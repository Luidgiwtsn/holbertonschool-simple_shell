#include "main.h"

/**
 * free_args - Free array of strings
 * @args: Array to free
 */
void free_args(char **args)
{
    int i;

    if (!args)
        return;

    for (i = 0; args[i] != NULL; i++)
        free(args[i]);

    free(args);
}
