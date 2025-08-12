#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

/**
 * main - Un shell très simple qui exécute les commandes par chemin absolu
 *
 * Ce programme :
 * - Affiche un prompt (#cisfun$)
 * - Lit une commande (sans arguments)
 * - Crée un processus enfant
 * - Exécute la commande avec execl
 * - Attend que l'enfant finisse
 *
 * Return: Toujours 0
 */
int main(void)
{
    char line[MAX_CMD_LEN];

    while (1)
    {
        /* Affiche le prompt */
        printf("#cisfun$ ");
        fflush(stdout);

        /* Lit la ligne entrée par l'utilisateur */
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            /* Ctrl+D ou erreur de lecture */
            printf("\n");
            break;
        }

        /* Supprime le saut de ligne final */
        line[strcspn(line, "\n")] = '\0';

        /* Ignore les lignes vides */
        if (line[0] == '\0')
            continue;

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Processus enfant : exécute la commande sans argument */
            execl(line, line, (char *)NULL);

            /* Si execl échoue */
            perror("exec erreur");
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Processus parent : attend la fin de l'enfant */
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return (0);
}