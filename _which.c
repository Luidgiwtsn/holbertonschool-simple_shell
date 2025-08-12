#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - Cherche les fichiers exécutables dans le $PATH
 * @argc: Nombre d'arguments
 * @argv: Liste des arguments
 *
 * Usage: ./_which fichier ...
 * Return: 0 si tout va bien, 1 en cas d'erreur
 */
int main(int argc, char *argv[])
{
    char *path, *dir, *env_path, full_path[1024];
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s fichier ...\n", argv[0]);
        return (1);
    }

    env_path = getenv("PATH");  // Récupère la variable d'environnement PATH
    if (env_path == NULL)
    {
        fprintf(stderr, "PATH non défini\n");
        return (1);
    }

    path = strdup(env_path); // On duplique PATH pour pouvoir le modifier
    if (path == NULL)
    {
        perror("strdup");
        return (1);
    }

    for (i = 1; i < argc; i++) // Pour chaque fichier fourni
    {
        int trouve = 0;
        char *path_copy = strdup(path);

        dir = strtok(path_copy, ":");
        while (dir != NULL)
        {
            snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[i]);

            if (access(full_path, X_OK) == 0) // Vérifie si le fichier est exécutable
            {
                printf("%s\n", full_path);
                trouve = 1;
                break;
            }

            dir = strtok(NULL, ":");
        }

        free(path_copy);

        if (!trouve)
        {
            // afficher une erreur si non trouvé
            fprintf(stderr, "%s : commande introuvable\n", argv[i]);
        }
    }

    free(path);
    return (0);
}