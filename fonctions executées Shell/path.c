#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *path_env, *path_copy, *token;

    /* Get the PATH environment variable */
    path_env = getenv("PATH");
    if (path_env == NULL)
    {
        fprintf(stderr, "PATH not found\n");
        return (1);
    }

    /* Duplicate it because strtok will modify the string */
    path_copy = strdup(path_env);
    if (path_copy == NULL)
    {
        perror("strdup");
        return (1);
    }

    /* Tokenize by ':' and print each directory */
    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return (0);
}
