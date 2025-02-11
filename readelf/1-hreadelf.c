#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * print_section_headers - Muestra las cabeceras de las secciones de un ELF
 * @fd: Archivo ELF abierto
 * @ehdr: Encabezado ELF
 */
void print_section_headers(int fd, Elf32_Ehdr *ehdr)
{
    Elf32_Shdr shdr;
    char *shstrtab;
    int i;

    lseek(fd, ehdr->e_shoff + (ehdr->e_shstrndx * sizeof(Elf32_Shdr)), SEEK_SET);
    read(fd, &shdr, sizeof(Elf32_Shdr));
    shstrtab = malloc(shdr.sh_size);
    lseek(fd, shdr.sh_offset, SEEK_SET);
    read(fd, shstrtab, shdr.sh_size);

    printf("There are %d section headers, starting at offset 0x%x:\n\n", ehdr->e_shnum, ehdr->e_shoff);
    printf("Section Headers:\n");
    printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");

    for (i = 0; i < ehdr->e_shnum; i++)
    {
        lseek(fd, ehdr->e_shoff + (i * sizeof(Elf32_Shdr)), SEEK_SET);
        read(fd, &shdr, sizeof(Elf32_Shdr));

        printf("  [%2d] %-17s %08x %08x %08x %08x %02x %02x %02x\n",
               i,
               shstrtab + shdr.sh_name,
               shdr.sh_type,
               shdr.sh_addr,
               shdr.sh_offset,
               shdr.sh_size,
               shdr.sh_flags,
               shdr.sh_link,
               shdr.sh_info);
    }

    free(shstrtab);
}

/**
 * main - Lee un archivo ELF y muestra sus secciones
 * @argc: Número de argumentos
 * @argv: Argumentos del programa
 * Return: EXIT_SUCCESS o EXIT_FAILURE
 */
int main(int argc, char **argv)
{
    int fd;
    Elf32_Ehdr ehdr;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }

    if (read(fd, &ehdr, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
    {
        perror("read");
        close(fd);
        return EXIT_FAILURE;
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0)
    {
        fprintf(stderr, "%s is not an ELF file\n", argv[1]);
        close(fd);
        return EXIT_FAILURE;
    }

    print_section_headers(fd, &ehdr);

    close(fd);
    return EXIT_SUCCESS;
}
