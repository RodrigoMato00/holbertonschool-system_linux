#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_elf(const char *filename);

#endif
