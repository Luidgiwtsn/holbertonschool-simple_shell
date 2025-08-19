#include "main.h"

/**
 * main - Simple shell main function
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
    char *line, **args = NULL;
    int status, line_number = 0;
    pid_t pid;
    (void) argc;

    while (1)
    {
        line = read_and_clean_line();
        if (line == NULL)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
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

        /* Handle exit command */
        if (strcmp(args[0], "exit") == 0)
        {
            free(line);
            free_args(args);
            break;
        }

        /* Handle cd command */
        if (strcmp(args[0], "cd") == 0)
        {
            const char *path = args[1] ? args[1] : _getenv("HOME");
            if (chdir(path) != 0)
            {
                fprintf(stderr, "hsh: %d: cd: can't cd to %s\n",
                        line_number, path ? path : "");
            }
            free(line);
            free_args(args);
            continue;
        }

        /* Execute other commands */
        pid = fork();
        if (pid == 0)
        {
            execve_hsh(args, line_number, argv[0]);
            exit(127);
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

    return (0);
}
