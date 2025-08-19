#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * struct PathNode - Node of a singly linked list that stores a directory path.
 * @directory: The directory path string.
 * @next: Pointer to the next node in the list.
 *
 * Description: This struct represent a directory in a linked list
 * of paths.
 */
typedef struct PathNode
{
	char *directory;
	struct PathNode *next;
} PathNode;


#define MAX_CMD_LEN 100

extern char **environ;


void free_path_list(PathNode *head);
void print_path_list(PathNode *head);
int count_directories(PathNode *head);
PathNode *build_path_list(void);
PathNode *create_node(const char *directory);
PathNode *parse_path(const char *path_env);

int _setenv(const char *name, const char *value, int overwrite);
void print_environ(void);
int _unsetenv(const char *name);

char *read_and_clean_line(void); 
char **split_line(char *line);  
void execve_hsh(char **args, int line_number);  
void free_args(char **args);
char *_getenv(const char *name);
char *find_in_path(const char *cmd);



char **smart_tokenize(const char *input); 

#endif 
