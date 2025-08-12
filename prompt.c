#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 1024
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;    
    while (1)
    {
        printf("$ ");
        nread = getline(&line, &len, stdin);
        if (nread == -1)  /* Fin du fichier (Ctrl+D) ou erreur */
            break;        /* Supprime le saut de ligne final s’il y en a un */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';        
            
            printf("%s\n", line);
    }    
    free(line);
    return 0;
}
