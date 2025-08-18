#include "main.h"

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
    int argc = 0;
    pid_t pid;

    while (1)
    {
      line = read_and_clean_line();
        if (line == NULL) // EOF or error
        {    printf("\n"); 
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
        argc = 0;
        while (args[argc] != NULL) 
        argc++;
        
        if (strcmp(args[0], "exit") == 0)
            {free(line);
            free_args(args);
            break;
            }
        // Commande "cd"
        if (strcmp(args[0], "cd") == 0)
        {
            const char *path = args[1] ? args[1] : _getenv("HOME"); // prendre le _getenv de l'exo
            if (chdir(path) != 0)
                perror("cd");
                  free(line);
            free_args(args);
            continue;
        }
        pid = fork();
        if (pid == 0)
        {
            execve_hsh(args, line_number);
             exit(EXIT_FAILURE); // fonction séparée
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




