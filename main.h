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

/* Define the maximum length of a command */
#define MAX_CMD_LEN 100

extern char **environ;

/* Function prototypes */
void free_path_list(PathNode *head);
void print_path_list(PathNode *head);
int count_directories(PathNode *head);
PathNode *build_path_list(void);
PathNode *create_node(const char *directory);
PathNode *parse_path(const char *path_env);


char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
void print_environ(void);
int _unsetenv(const char *name);




char **smart_tokenize(const char *input); /* decour en tokens sur une cdopie donc safe */
```

#endif /* __MAIN_H__ */
