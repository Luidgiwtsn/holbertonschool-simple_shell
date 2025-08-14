#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("#cisfun$ ");

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            break;  // Ctrl+D
        }

        line[strcspn(line, "\n")] = '\0';  // Supprime le \n

        if (strcmp(line, "exit") == 0)
            break;

        if (strlen(line) == 0)
            continue;  // Ligne vide

        pid = fork();
        if (pid == 0)
        {
            char *argv[] = {line, NULL};
            execve(argv[0], argv, environ);
            perror("./shell");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }
        else
        {
            perror("fork");
        }
    }

    free(line);
    return 0;
}
