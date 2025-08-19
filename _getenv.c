#include "main.h"

/**
 * _getenv - Get environment variable value
 * @name: Variable name
 *
 * Return: Variable value or NULL
 */
char *_getenv(const char *name)
{
    int i;
    size_t name_len;
    char *var_env, *pos_egal;

    if (name == NULL || *name == '\0')
        return (NULL);

    name_len = strlen(name);

    for (i = 0; environ[i] != NULL; i++)
    {
        var_env = environ[i];
        pos_egal = strchr(var_env, '=');

        if (pos_egal == NULL)
            continue;

        if ((size_t)(pos_egal - var_env) == name_len &&
            strncmp(var_env, name, name_len) == 0)
        {
            return (pos_egal + 1);
        }
    }

    return (NULL);
}
