#include "elf_parser.h"

/**
 * print_symbol_type - Determine symbol type character
 * @sym: ELF symbol
 * Return: Symbol type character
 */
char print_symbol_type(Elf64_Sym sym)
{
	char type;

	switch (ELF64_ST_BIND(sym.st_info))
	{
	case STB_WEAK:
		if (sym.st_shndx == SHN_UNDEF)
			type = 'w';
		else
			type = 'W';
		break;
	default:
		switch (sym.st_shndx)
		{
		case SHN_UNDEF:
			type = 'U';
			break;
		case SHN_ABS:
			type = 'A';
			break;
		case SHN_COMMON:
			type = 'C';
			break;
		default:
			switch (ELF64_ST_TYPE(sym.st_info))
			{
			case STT_OBJECT:
				type = 'D';
				break;
			case STT_FUNC:
				type = 'T';
				break;
			case STT_SECTION:
				type = 'N';
				break;
			case STT_FILE:
				type = 'F';
				break;
			default:
				type = '?';
			}
		}
	}
	return (type);
}

/**
 * print_symbols - print ELF symbols
 * @file: FILE pointer
 * @symtab: Symbol table
 * @strtab: String table
 */
void print_symbols(FILE *file, Elf64_Shdr symtab, Elf64_Shdr strtab)
{
	Elf64_Sym *symbols;
	char *strs;
	size_t symbol_count, j;
	char type;

	symbols = malloc(symtab.sh_size);
	strs = malloc(strtab.sh_size);

	fseek(file, symtab.sh_offset, SEEK_SET);
	fread(symbols, symtab.sh_size, 1, file);

	fseek(file, strtab.sh_offset, SEEK_SET);
	fread(strs, strtab.sh_size, 1, file);

	symbol_count = symtab.sh_size / sizeof(Elf64_Sym);

	for (j = 0; j < symbol_count; j++)
	{
		if (symbols[j].st_name != 0)
		{
			type = print_symbol_type(symbols[j]);
			printf("%016lx %c %s\n",
				symbols[j].st_value, type,
				strs + symbols[j].st_name);
		}
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
	FILE *file;
	Elf64_Ehdr ehdr;
	Elf64_Shdr *shdr;
	int i;

	file = fopen(filename, "rb");
	if (!file)
	{
		perror("Error al abrir archivo");
		exit(EXIT_FAILURE);
	}

	fread(&ehdr, sizeof(ehdr), 1, file);

	shdr = malloc(sizeof(Elf64_Shdr) * ehdr.e_shnum);
	fseek(file, ehdr.e_shoff, SEEK_SET);
	fread(shdr, sizeof(Elf64_Shdr), ehdr.e_shnum, file);

	for (i = 0; i < ehdr.e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB ||
			shdr[i].sh_type == SHT_DYNSYM)
		{
			print_symbols(file, shdr[i], shdr[shdr[i].sh_link]);
		}
	}

	free(shdr);
	fclose(file);
}
