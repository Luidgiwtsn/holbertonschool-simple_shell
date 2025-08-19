#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>   

#define MAX_ARGS 100

char *read_and_clean_line(void);
char **split_line(char *line);
void execve_hsh(char **args, int line_number);
void free_args(char **args);
char *_getenv(const char *name);

int main(void)

{
    char *line, **args = NULL;
    int status, line_number = 0;
    
    pid_t pid;
    int interactive = isatty(STDIN_FILENO);

    while (1)
    {
        /* Le prompt est géré dans read_and_clean_line */
        line = read_and_clean_line();
        if (line == NULL) 
        {    
            if (interactive)
                printf("\n"); 
            break;
        }
        
        args = split_line(line);
        if (args[0] == NULL)
        {
            free(line);
            free_args(args);
            continue;
        }
        
        line_number++;
        
        /* Gestion de la commande exit */
        if (strcmp(args[0], "exit") == 0)
        {
            free(line);
            free_args(args);
            break;
        }
       
        /* Gestion de la commande cd */
        if (strcmp(args[0], "cd") == 0)
        {
            const char *path = args[1] ? args[1] : _getenv("HOME"); 
            if (chdir(path) != 0)
            {
                /* Format d'erreur spécifique pour Holberton */
                fprintf(stderr, "./hsh: %d: cd: can't cd to %s\n", 
                       line_number, path ? path : "NULL");
            }
            free(line);
            free_args(args);
            continue;
        }
        
        /* Exécution des autres commandes */
        pid = fork();
        if (pid == 0)
        {
            execve_hsh(args, line_number);
            exit(EXIT_FAILURE); 
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
        }
        else
        {
            perror("fork");
        }

        free(line);
        free_args(args);
    }

    return 0;
}

