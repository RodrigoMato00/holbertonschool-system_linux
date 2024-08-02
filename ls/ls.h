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
int _strcmp(const void *a, const void *b);
void selection_sort(char **arr, int n);
void process_args(int argc, char *argv[], char **dirs, char **files, int *dir_count, int *file_count);

#endif /* LS_H */
