#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>
#include <errno.h>

/* We are only allowed up to 5 functions, so we'll group logic carefully. */

/**
 * swap_endian_16 - Swap a 16-bit value if needed (big <-> little).
 * @val: Pointer to the 16-bit value to swap in place.
 */
static void swap_endian_16(unsigned short *val)
{
	unsigned short swapped = 0;

	swapped |= (*val & 0x00FF) << 8;
	swapped |= (*val & 0xFF00) >> 8;
	*val = swapped;
}

/**
 * swap_endian_32 - Swap a 32-bit value if needed (big <-> little).
 * @val: Pointer to the 32-bit value to swap in place.
 */
static void swap_endian_32(unsigned int *val)
{
	unsigned int swapped = 0;

	swapped |= (*val & 0x000000FF) << 24;
	swapped |= (*val & 0x0000FF00) << 8;
	swapped |= (*val & 0x00FF0000) >> 8;
	swapped |= (*val & 0xFF000000) >> 24;
	*val = swapped;
}

/**
 * swap_endian_64 - Swap a 64-bit value if needed (big <-> little).
 * @val: Pointer to the 64-bit value to swap in place.
 */
static void swap_endian_64(unsigned long *val)
{
	unsigned long swapped = 0;

	swapped |= (*val & 0x00000000000000FFUL) << 56;
	swapped |= (*val & 0x000000000000FF00UL) << 40;
	swapped |= (*val & 0x0000000000FF0000UL) << 24;
	swapped |= (*val & 0x00000000FF000000UL) << 8;
	swapped |= (*val & 0x000000FF00000000UL) >> 8;
	swapped |= (*val & 0x0000FF0000000000UL) >> 24;
	swapped |= (*val & 0x00FF000000000000UL) >> 40;
	swapped |= (*val & 0xFF00000000000000UL) >> 56;
	*val = swapped;
}

/**
 * main - Entry point, displays the ELF file header info (like readelf -W -h).
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, various error codes on failure
 *
 * We are staying under 5 total functions by consolidating code within main.
 */
int main(int argc, char **argv)
{
	int fd;
	ssize_t r;
	unsigned char e_ident[EI_NIDENT];
	int is_64, is_be;
	Elf32_Ehdr hdr32;
	Elf64_Ehdr hdr64;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error: Cannot open file '%s': %s\n",
			argv[1], strerror(errno));
		return (1);
	}

	/* Read the e_ident first to determine file class (32/64) & endianness */
	r = read(fd, e_ident, EI_NIDENT);
	if (r < (ssize_t)EI_NIDENT)
	{
		fprintf(stderr, "Error: '%s' is too small to be an ELF file\n", argv[1]);
		close(fd);
		return (1);
	}

	/* Check the ELF magic bytes */
	if (e_ident[0] != 0x7f || e_ident[1] != 'E' ||
	    e_ident[2] != 'L'  || e_ident[3] != 'F')
	{
		fprintf(stderr, "Error: '%s' is not an ELF file\n", argv[1]);
		close(fd);
		return (1);
	}

	is_64 = (e_ident[EI_CLASS] == ELFCLASS64);
	is_be = (e_ident[EI_DATA] == ELFDATA2MSB);

	/* Reposition file offset back to start to read full header */
	lseek(fd, 0, SEEK_SET);

	if (is_64)
	{
		r = read(fd, &hdr64, sizeof(hdr64));
		if (r < (ssize_t)sizeof(hdr64))
		{
			fprintf(stderr, "Error: Incomplete ELF64 header\n");
			close(fd);
			return (1);
		}
		if (is_be)
		{
			/* Swap multi-byte fields from big to little if needed */
			swap_endian_16(&hdr64.e_type);
			swap_endian_16(&hdr64.e_machine);
			swap_endian_32(&hdr64.e_version);
			swap_endian_64(&hdr64.e_entry);
			swap_endian_64(&hdr64.e_phoff);
			swap_endian_64(&hdr64.e_shoff);
			swap_endian_32(&hdr64.e_flags);
			swap_endian_16(&hdr64.e_ehsize);
			swap_endian_16(&hdr64.e_phentsize);
			swap_endian_16(&hdr64.e_phnum);
			swap_endian_16(&hdr64.e_shentsize);
			swap_endian_16(&hdr64.e_shnum);
			swap_endian_16(&hdr64.e_shstrndx);
		}

		/* Print the header in readelf -W -h format */
		printf("ELF Header:\n");
		/* Magic */
		printf("  Magic:   ");
		for (int i = 0; i < EI_NIDENT; i++)
			printf("%02x%c", hdr64.e_ident[i],
			       (i < EI_NIDENT - 1) ? ' ' : '\n');

		/* Class */
		printf("  Class:                             ");
		if (hdr64.e_ident[EI_CLASS] == ELFCLASS64)
			printf("ELF64\n");
		else
			printf("ELF32\n");

		/* Data */
		printf("  Data:                              ");
		if (hdr64.e_ident[EI_DATA] == ELFDATA2LSB)
			printf("2's complement, little endian\n");
		else if (hdr64.e_ident[EI_DATA] == ELFDATA2MSB)
			printf("2's complement, big endian\n");
		else
			printf("Invalid data encoding\n");

		/* Version (e_ident) */
		printf("  Version:                           %d",
		       hdr64.e_ident[EI_VERSION]);
		if (hdr64.e_ident[EI_VERSION] == EV_CURRENT)
			printf(" (current)\n");
		else
			printf("\n");

		/* OS/ABI */
		printf("  OS/ABI:                            ");
		switch (hdr64.e_ident[EI_OSABI])
		{
		case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
		case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
		case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
		case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
		default: printf("<unknown: %x>\n", hdr64.e_ident[EI_OSABI]); break;
		}

		/* ABI Version */
		printf("  ABI Version:                       %d\n",
		       hdr64.e_ident[EI_ABIVERSION]);

		/* Type */
		printf("  Type:                              ");
		switch (hdr64.e_type)
		{
		case ET_NONE: printf("NONE (No file type)\n"); break;
		case ET_REL: printf("REL (Relocatable file)\n"); break;
		case ET_EXEC: printf("EXEC (Executable file)\n"); break;
		case ET_DYN: printf("DYN (Shared object file)\n"); break;
		case ET_CORE: printf("CORE (Core file)\n"); break;
		default: printf("<unknown>: %x\n", hdr64.e_type);
		}

		/* Machine */
		printf("  Machine:                           ");
		switch (hdr64.e_machine)
		{
		case EM_386: printf("Intel 80386\n"); break;
		case EM_X86_64: printf("Advanced Micro Devices X86-64\n"); break;
		case EM_SPARC: printf("Sparc\n"); break;
		case EM_ARM: printf("ARM\n"); break;
		case EM_PPC: printf("PowerPC\n"); break;
		case EM_PPC64: printf("PowerPC64\n"); break;
		default: printf("<unknown>: %x\n", hdr64.e_machine);
		}

		/* Version (e_version) */
		printf("  Version:                           0x%x\n", hdr64.e_version);

		/* Entry point */
		printf("  Entry point address:               0x%lx\n",
		       (unsigned long)hdr64.e_entry);

		/* Start of program headers */
		printf("  Start of program headers:          %ld (bytes into file)\n",
		       (long)hdr64.e_phoff);

		/* Start of section headers */
		printf("  Start of section headers:          %ld (bytes into file)\n",
		       (long)hdr64.e_shoff);

		/* Flags */
		printf("  Flags:                             0x%x\n", hdr64.e_flags);

		/* Size of this header */
		printf("  Size of this header:               %d (bytes)\n",
		       hdr64.e_ehsize);

		/* Size of program headers */
		printf("  Size of program headers:           %d (bytes)\n",
		       hdr64.e_phentsize);

		/* Number of program headers */
		printf("  Number of program headers:         %d\n", hdr64.e_phnum);

		/* Size of section headers */
		printf("  Size of section headers:           %d (bytes)\n",
		       hdr64.e_shentsize);

		/* Number of section headers */
		printf("  Number of section headers:         %d\n", hdr64.e_shnum);

		/* Section header string table index */
		printf("  Section header string table index: %d\n", hdr64.e_shstrndx);
	}
	else /* 32-bit ELF */
	{
		r = read(fd, &hdr32, sizeof(hdr32));
		if (r < (ssize_t)sizeof(hdr32))
		{
			fprintf(stderr, "Error: Incomplete ELF32 header\n");
			close(fd);
			return (1);
		}
		if (is_be)
		{
			/* Swap multi-byte fields for big endian */
			swap_endian_16(&hdr32.e_type);
			swap_endian_16(&hdr32.e_machine);
			swap_endian_32(&hdr32.e_version);
			swap_endian_32(&hdr32.e_entry);
			swap_endian_32(&hdr32.e_phoff);
			swap_endian_32(&hdr32.e_shoff);
			swap_endian_32(&hdr32.e_flags);
			swap_endian_16(&hdr32.e_ehsize);
			swap_endian_16(&hdr32.e_phentsize);
			swap_endian_16(&hdr32.e_phnum);
			swap_endian_16(&hdr32.e_shentsize);
			swap_endian_16(&hdr32.e_shnum);
			swap_endian_16(&hdr32.e_shstrndx);
		}

		printf("ELF Header:\n");
		/* Magic */
		printf("  Magic:   ");
		for (int i = 0; i < EI_NIDENT; i++)
			printf("%02x%c", hdr32.e_ident[i],
			       (i < EI_NIDENT - 1) ? ' ' : '\n');

		/* Class */
		printf("  Class:                             ");
		if (hdr32.e_ident[EI_CLASS] == ELFCLASS64)
			printf("ELF64\n");
		else
			printf("ELF32\n");

		/* Data */
		printf("  Data:                              ");
		if (hdr32.e_ident[EI_DATA] == ELFDATA2LSB)
			printf("2's complement, little endian\n");
		else if (hdr32.e_ident[EI_DATA] == ELFDATA2MSB)
			printf("2's complement, big endian\n");
		else
			printf("Invalid data encoding\n");

		/* Version (e_ident) */
		printf("  Version:                           %d",
		       hdr32.e_ident[EI_VERSION]);
		if (hdr32.e_ident[EI_VERSION] == EV_CURRENT)
			printf(" (current)\n");
		else
			printf("\n");

		/* OS/ABI */
		printf("  OS/ABI:                            ");
		switch (hdr32.e_ident[EI_OSABI])
		{
		case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
		case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
		case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
		case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
		default: printf("<unknown: %x>\n", hdr32.e_ident[EI_OSABI]); break;
		}

		/* ABI Version */
		printf("  ABI Version:                       %d\n",
		       hdr32.e_ident[EI_ABIVERSION]);

		/* Type */
		printf("  Type:                              ");
		switch (hdr32.e_type)
		{
		case ET_NONE: printf("NONE (No file type)\n"); break;
		case ET_REL: printf("REL (Relocatable file)\n"); break;
		case ET_EXEC: printf("EXEC (Executable file)\n"); break;
		case ET_DYN: printf("DYN (Shared object file)\n"); break;
		case ET_CORE: printf("CORE (Core file)\n"); break;
		default: printf("<unknown>: %x\n", hdr32.e_type);
		}

		/* Machine */
		printf("  Machine:                           ");
		switch (hdr32.e_machine)
		{
		case EM_386: printf("Intel 80386\n"); break;
		case EM_X86_64: printf("Advanced Micro Devices X86-64\n"); break;
		case EM_SPARC: printf("Sparc\n"); break;
		case EM_ARM: printf("ARM\n"); break;
		case EM_PPC: printf("PowerPC\n"); break;
		case EM_PPC64: printf("PowerPC64\n"); break;
		default: printf("<unknown>: %x\n", hdr32.e_machine);
		}

		/* Version (e_version) */
		printf("  Version:                           0x%x\n", hdr32.e_version);

		/* Entry point */
		printf("  Entry point address:               0x%lx\n",
		       (unsigned long)hdr32.e_entry);

		/* Program headers offset */
		printf("  Start of program headers:          %ld (bytes into file)\n",
		       (long)hdr32.e_phoff);

		/* Section headers offset */
		printf("  Start of section headers:          %ld (bytes into file)\n",
		       (long)hdr32.e_shoff);

		/* Flags */
		printf("  Flags:                             0x%x\n", hdr32.e_flags);

		/* Size of this header */
		printf("  Size of this header:               %d (bytes)\n",
		       hdr32.e_ehsize);

		/* Size of program headers */
		printf("  Size of program headers:           %d (bytes)\n",
		       hdr32.e_phentsize);

		/* Number of program headers */
		printf("  Number of program headers:         %d\n", hdr32.e_phnum);

		/* Size of section headers */
		printf("  Size of section headers:           %d (bytes)\n",
		       hdr32.e_shentsize);

		/* Number of section headers */
		printf("  Number of section headers:         %d\n", hdr32.e_shnum);

		/* String table index */
		printf("  Section header string table index: %d\n", hdr32.e_shstrndx);
	}

	close(fd);
	return (0);
}
