#ifndef LS_H
#define LS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void list_directory(const char *path);
int is_directory(const char *path);
int _strcmp(const char *str1, const char *str2);
char _tolower(char c);
void selection_sort(char **arr, int n);
void process_args(int argc, char *argv[], char **dirs, char **files, int *dir_count, int *file_count);
void print_dirs_and_files(char **dirs, char **files, int dir_count, int file_count);
void selection_sort_dirent(struct dirent **arr, int n);
int compare_dirent(const struct dirent *a, const struct dirent *b);
struct dirent **count_entries(const char *path, int *num_entries);
int _entries(struct dirent ***entries, int size);

#endif /* LS_H */
