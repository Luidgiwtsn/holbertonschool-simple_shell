#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **split_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");  // découpe avec espace et tabulation comme séparateurs
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;  // Terminer le tableau par NULL comme av

    return tokens;
}

int main(void)
{
    char line[] = "ls -l /home/user";
    char **args = split_line(line);
    int i = 0;

    while (args[i] != NULL)
    {
        printf("arg[%d]: %s\n", i, args[i]);
        i++;
    }
    free(args);  // Attention : ici on libère le tableau mais pas les chaînes (car strtok modifie la ligne originale)

    return 0;
}
