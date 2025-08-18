#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "main.h"



char **split_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token; char **tmp;

    if (!tokens) return NULL;

    token = strtok(line, " \t\r\n");
    while (token)
    {
        if (position >= bufsize - 1) {
            bufsize *= 2;
            tmp = realloc(tokens, bufsize * sizeof(char *));
            if (!tmp) { free(tokens); return NULL; }
            tokens = tmp;
        }
        tokens[position++] = strdup(token);  // <-- dupliquer
        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;
    return tokens;
}
