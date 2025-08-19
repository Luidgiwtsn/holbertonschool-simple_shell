#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"  

void execve_hsh(char **args, int line_number)
{
    char *cmd_path;
    (void)line_number; 

    if (args[0][0] == '/' || args[0][0] == '.')
    {
        cmd_path = args[0]; 
    }
    else
    {
        cmd_path = find_in_path(args[0]);
        if (!cmd_path)
        {
            fprintf(stderr, "hsh: %d: %s: command not found\n", line_number, args[0]);
            exit(127);
        }
    }

    if (execve(cmd_path, args, environ) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}
