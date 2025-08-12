#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Exécute "ls -l /tmp" dans 5 processus enfants, un par un
 *
 * Return: Toujours 0
 */
int main(void)
{
    // Commande à exécuter
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
    pid_t pid;
    int i, status;

    for (i = 0; i < 5; i++)
    {
        pid = fork();  // Création d'un processus enfant

        if (pid == -1)
        {
            // Erreur lors du fork
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Code exécuté par l’enfant
            printf("Enfant %d en cours d'exécution :\n", i + 1);
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Code exécuté par le père
            wait(&status);  // Attente de la fin de l’enfant
            printf("Enfant %d terminé.\n\n", i + 1);
        }
    }

    return (0);
}