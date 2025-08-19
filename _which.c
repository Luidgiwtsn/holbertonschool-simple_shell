#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * file_exists - Vérifie si un fichier existe et est exécutable
 * @path: Chemin complet du fichier
 *
 * Return: 1 si le fichier existe et est exécutable, 0 sinon
 */
int file_exists(const char *path)
{
    struct stat st;
    return (stat(path, &st) == 0 && (st.st_mode & S_IXUSR));
}

/**
 * _which - Cherche un programme dans le PATH
 * @cmd: Nom de la commande (ex: "ls")
 *
 * Return: Chemin complet du programme si trouvé, NULL sinon
 *         (le résultat doit être free après usage)
 */
char *_which(const char *cmd)
{
    char *path_env, *path_copy, *dir, *full_path;
    size_t len;

    path_env = getenv("PATH");
    if (path_env == NULL)
        return NULL;

    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        len = strlen(dir) + strlen(cmd) + 2; // 1 pour '/' et 1 pour '\0'
        full_path = malloc(len);
        if (full_path == NULL)
        {
            free(path_copy);
            return NULL;
        }

        snprintf(full_path, len, "%s/%s", dir, cmd);
        if (file_exists(full_path))
        {
            free(path_copy);
            return full_path; // trouve -> retourne le chemin complet
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL; // pas trouvé
}

/* Exemple d'utilisation */
int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s command_name\n", argv[0]);
        return 1;
    }

    result = _which(argv[1]);
    if (result)
    {
        printf("%s\n", result);
        free(result);
    }
    else
        printf("Command not found\n");

    return 0;
}
