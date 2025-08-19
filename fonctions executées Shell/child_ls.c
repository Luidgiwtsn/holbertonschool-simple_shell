#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child_pid;
    int status;
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
    int i;

    for (i = 0; i < 5; i++) // 5 enfants
    {
        child_pid = fork(); // Crée un enfant

        if (child_pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (child_pid == 0) // Code de l'enfant
        {
            printf("Enfant %d : je lance la commande\n", i + 1);
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("execve");
            }
            return 1; // On sort si execve échoue
        }
        else // Code du père
        {
            wait(&status); // Attend que l'enfant finisse
            printf("Père : l'enfant %d a fini\n", i + 1);
        }
    }

    return 0;
}
/**
 * fork_wait_execve - Example of using fork, wait, and execve
 *
 * This program creates multiple child processes that execute a command
 * and waits for each child to finish before proceeding.
 *
 * Return: Always 0.
 */
