# ELF Parsing Project

## Introduction
This project is designed to deepen your understanding of the Executable and Linkable Format (ELF), and tools used for ELF file analysis, namely `nm` and `objdump`. You will recreate simplified versions of these GNU tools (`hnm` and `hobjdump`) to better understand how ELF files are structured and parsed.

## Learning Objectives

By the end of this project, you should be able to explain clearly:

- What the ELF format is.
- What the `nm` and `objdump` commands do.
- How to use these commands properly.
- How to parse the content of ELF files.
- What kind of information can be extracted from ELF files.
- The differences between `nm` and `objdump`.

## Resources

- [ELF Wikipedia](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)
- [Executable and Linkable Format (ELF)](https://wiki.osdev.org/ELF)
- [The ELF Object File Format: Introduction](http://www.skyfree.org/linux/references/ELF_Format.pdf)
- [The ELF Object File Format by Dissection](https://medium.com/@ayushgoyal/the-elf-object-file-format-by-dissection-7d5f44e6b44b)

### Man Pages:
- `elf(5)`
- `nm (1)`
- `objdump (1)`

## Requirements

- Allowed editors: `vi`, `vim`, `emacs`
- Your files will be compiled on Ubuntu 20.04 LTS.
- Compilation using gcc 9.4.0 with flags `-Wall -Werror -Wextra -pedantic`.
- Code must follow the Betty style.
- A `README.md` at the root of the project directory is mandatory.
- Files must end with a newline.
- Maximum of 5 functions per file.
- All header files must be include guarded.

### Restrictions
- You are allowed to use the C standard library unless otherwise specified.
- Use of `system(3)` and `exec*(2,3)` is not permitted.

### Supported ELF Files

Your program must correctly handle:
- 32-bit and 64-bit ELF files
- Little and big endian ELF files
- All types of ELF files (executable, object, shared libraries)

## Project Structure

```
nm_objdump/
├── Makefile
├── README.md
├── hnm (your nm clone)
├── hobjdump (your objdump implementation)
└── src/
    ├── elf_parser.c
    ├── elf_parser.h
    ├── hnm.c
    └── hobjdump.c

## Commands

### hnm
Replicates the behavior of `nm -p`.

```bash
Usage: ./hnm [objfile ...]
```

Example:
```bash
./hnm elf_files/ubuntu64
```

Output matches `nm -p [objfile]`.

### hobjdump
Replicates the behavior of `objdump -sf`.

Usage:
```
hobjdump [objfile ...]
```

Example:
```bash
./hobjdump elf_files/ubuntu64
```

This will output the sections and contents of ELF files exactly like the `objdump -sf` command.

## Compiling the Project

Use the provided `Makefile` to compile your programs:

```bash
make hnm
make hobjdump
```

## Example Usage

### hnm Example

```bash
./hnm elf_files/ubuntu64
```

### hobjdump

```bash
./hobjdump elf_files/ubuntu64
```

## Understanding ELF Files

### What is ELF?
ELF (Executable and Linkable Format) is a common binary format used by Unix and Linux operating systems for executables, object code, shared libraries, and core dumps.

### nm
`nm` lists symbols from object files, showing symbol names, their addresses, and types.

### objdump
`objdump` provides detailed information about the content of ELF files, including sections, symbols, and assembly code.

### Differences between nm and objdump
- `nm` lists symbols from object files (such as functions and variables).
- `objdump` provides detailed section content and disassembly.

### ELF Parsing
Parsing involves reading ELF headers, section headers, symbol tables, and program headers. You can utilize functions provided by the ELF standard in `<elf.h>`.

### Useful Commands
- `nm -p`: Lists symbols in the order they appear in the binary.
- `objdump -sf`: Dumps section headers and contents in formatted form.

## Compiling and Running Your Project

To build the project, use:

```bash
make
```

Or individually:

```bash
make hnm
make hobjdump
```

### Cleanup
To remove executable files and object files:

```bash
make clean
```

Author: Rodrigo Mato
Date: March 2025

