#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * find_in_path - cherche une commande dans les répertoires du PATH
 * @cmd: la commande à chercher (ex: "ls")
 *
 * Return: chemin complet (malloc) si trouvé, NULL sinon
 *         → Il faut free() le retour dans l'appelant !
 */
char *find_in_path(const char *cmd)
{
    char *path_env;
    char *path_copy;
    char *dir;
    char *full_path;
    size_t len;

    path_env = getenv("PATH");
    if (!path_env)
        return NULL;


        path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        len = strlen(dir) + strlen(cmd) + 2;
        full_path = malloc(len);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }

        snprintf(full_path, len, "%s/%s", dir, cmd);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
