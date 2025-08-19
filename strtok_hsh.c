#include "main.h"

/**
 * split_line - Split line into tokens
 * @line: Line to split
 *
 * Return: Array of tokens
 */
char **split_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token, **tmp;

    if (!tokens)
        return (NULL);

    token = strtok(line, " \t\r\n");
    while (token)
    {
        if (position >= bufsize - 1)
        {
            bufsize *= 2;
            tmp = realloc(tokens, bufsize * sizeof(char *));
            if (!tmp)
            {
                free(tokens);
                return (NULL);
            }
            tokens = tmp;
        }

        tokens[position++] = strdup(token);
        token = strtok(NULL, " \t\r\n");
    }

    tokens[position] = NULL;
    return (tokens);
}
