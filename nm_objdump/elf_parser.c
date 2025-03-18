#include "elf_parser.h"

/**
 * print_symbols - print ELF symbols
 * @file: FILE pointer
 * @shdr: Section headers
 * @strtab: String table
 * @symtab: Symbol table
 */
void print_symbols(FILE *file, Elf64_Shdr symtab, Elf64_Shdr strtab)
{
	Elf64_Sym *symbols = malloc(symtab.sh_size);
	char *strs = malloc(strtab.sh_size);

	fseek(file, symtab.sh_offset, SEEK_SET);
	fread(symbols, symtab.sh_size, 1, file);

	fseek(file, strtab.sh_offset, SEEK_SET);
	fread(strs, strtab.sh_size, 1, file);

	size_t symbol_count = symtab.sh_size / sizeof(Elf64_Sym);

	for (size_t j = 0; j < symbol_count; j++)
	{
		char type;

		switch (ELF64_ST_BIND(symbols[j].st_info))
		{
		case STB_WEAK:
			type = (symbols[j].st_shndx == SHN_UNDEF) ? 'w' : 'W';
			break;
		default:
			switch (symbols[j].st_shndx)
			{
			case SHN_UNDEF: type = 'U'; break;
			case SHN_ABS:   type = 'A'; break;
			case SHN_COMMON:type = 'C'; break;
			default:
				switch (ELF64_ST_TYPE(symbols[j].st_info))
				{
				case STT_OBJECT: type = 'D'; break;
				case STT_FUNC:   type = 'T'; break;
				case STT_SECTION:type = 'N'; break;
				case STT_FILE:   type = 'F'; break;
				default:         type = '?';
				}
			}
		}

		if (symbols[j].st_name != 0)
			printf("%016lx %c %s\n",
				symbols[j].st_value, type,
				strs + symbols[j].st_name);
	}

	free(symbols);
	free(strs);
}

/**
 * parse_elf - Parse ELF file and print symbols
 * @filename: path to ELF file
 */
void parse_elf(const char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (!file)
	{
		perror("Error al abrir archivo");
		exit(EXIT_FAILURE);
	}

	Elf64_Ehdr ehdr;
	fread(&ehdr, sizeof(ehdr), 1, file);

	Elf64_Shdr shdr[ehdr.e_shnum];
	fseek(file, ehdr.e_shoff, SEEK_SET);
	fread(shdr, sizeof(Elf64_Shdr), ehdr.e_shnum, file);

	for (int i = 0; i < ehdr.e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB || shdr[i].sh_type == SHT_DYNSYM)
		{
			Elf64_Shdr symtab = shdr[i];
			Elf64_Shdr strtab = shdr[symtab.sh_link];

			print_symbols(file, symtab, strtab);
		}
	}

	fclose(file);
}
