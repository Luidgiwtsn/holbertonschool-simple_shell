#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _unsetenv - Custom implementation of unsetenv
 * @name: Name of the environment variable to remove
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
    int i, j;
    size_t len;

    if (!name || strchr(name, '='))
        return -1;

    len = strlen(name);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            // Free the string if dynamically allocated (optional)
            // Shift remaining environment variables
            for (j = i; environ[j]; j++)
                environ[j] = environ[j + 1];
            return 0;
        }
    }

    return -1; // Not found
}
