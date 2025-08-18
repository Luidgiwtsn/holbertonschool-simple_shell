#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
/**
 * free_args - Free an array of strings (arguments).
 * @args: The array of strings to free.
 *
 * Description: This function frees each string in the array
 * and then frees the array itself.
 */

void free_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}
