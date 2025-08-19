#include "main.h"

/**
 * find_in_path - Find command in PATH directories
 * @cmd: Command to find
 *
 * Return: Full path if found, NULL otherwise
 */
char *find_in_path(const char *cmd)
{
    char *path_env, *path_copy, *dir, *full_path;
    size_t len;

    path_env = _getenv("PATH");
    if (!path_env)
        return (NULL);

    path_copy = malloc(strlen(path_env) + 1);
    if (!path_copy)
        return (NULL);
    strcpy(path_copy, path_env);

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        len = strlen(dir) + strlen(cmd) + 2;
        full_path = malloc(len);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }

        sprintf(full_path, "%s/%s", dir, cmd);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
