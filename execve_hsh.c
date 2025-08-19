#include "main.h"

/**
 * execve_hsh - Execute command using execve
 * @args: Arguments array
 * @line_number: Line number for error messages
 * @shell_name: Name of shell (argv[0])
 */
void execve_hsh(char **args, int line_number, char *shell_name)
{
    char *cmd_path = NULL;
    int path_allocated = 0;

    if (args[0][0] == '/' || args[0][0] == '.')
    {
        cmd_path = args[0];
        if (access(cmd_path, F_OK) != 0)
        {
            fprintf(stderr, "%s: %d: %s: not found\n", shell_name, line_number, args[0]);
            exit(127);
        }
        if (access(cmd_path, X_OK) != 0)
        {
            fprintf(stderr, "%s: %d: %s: Permission denied\n", shell_name, line_number, args[0]);
            exit(126);
        }
    }
    else
    {
        cmd_path = find_in_path(args[0]);
        if (!cmd_path)
        {
            fprintf(stderr, "%s: %d: %s: not found\n", shell_name, line_number, args[0]);
            exit(127);
        }
        path_allocated = 1;
    }

    if (execve(cmd_path, args, environ) == -1)
    {
        perror("execve");
        if (path_allocated)
            free(cmd_path);
        exit(EXIT_FAILURE);
    }

    if (path_allocated)
        free(cmd_path);
}
