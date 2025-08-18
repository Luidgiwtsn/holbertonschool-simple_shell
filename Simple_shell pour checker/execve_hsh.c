#include <stdio.h>
#include <unistd.h>


extern char **environ;

void execve_hsh()
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

    printf("Before execve\n");
    if (execve(argv[0], argv, NULL) == -1)
    {
        perror("Error:");
    }

    // Cette ligne ne sera jamais atteinte si execve réussit
    printf("After execve\n");
}
