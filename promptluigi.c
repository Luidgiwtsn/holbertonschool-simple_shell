#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while (1)
    {
        printf("$ ");
        fflush(stdout);  // afficher immédiatement le prompt
        nread = getline(&line, &len, stdin);
        if (nread == -1)  // EOF détecté (Ctrl+D) ou erreur
        {
            printf("\nFin de lecture détectée. Arrêt du programme.\n");
            break;
        }
        // Affiche la ligne saisie (avec le saut de ligne déjà inclus)
        printf("%s", line);
    }
    free(line);
    return 0;
}
