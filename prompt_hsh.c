#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * read_and_clean_line - Affiche le prompt si nécessaire, lit une ligne,
 *                       et supprime le saut de ligne final.
 *
 * Return: La ligne lue (à libérer avec free), ou NULL en cas d'erreur ou EOF
 */
char *read_and_clean_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    if (isatty(STDIN_FILENO))
    {
        printf("hsh>$ ");
        fflush(stdout);
    }

    nread = getline(&line, &len, stdin);
    if (nread == -1)
    {
        free(line);
        return NULL;
    }

    if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';

    return line;
}
