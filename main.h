#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Function prototypes */
char *read_and_clean_line(void);
char **split_line(char *line);
void execve_hsh(char **args, int line_number, char *shell_name);
void free_args(char **args);
char *_getenv(const char *name);
char *find_in_path(const char *cmd);

#endif
