#include "main.h"

/**
 * read_and_clean_line - Read input and clean newline
 *
 * Return: The line read, or NULL on EOF
 */
char *read_and_clean_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    if (isatty(STDIN_FILENO))
    {
        write(STDOUT_FILENO, "$ ", 2);
    }

    nread = getline(&line, &len, stdin);
    if (nread == -1)
    {
        if (line)
            free(line);
        return (NULL);
    }

    if (nread > 0 && line[nread - 1] == '\n')
        line[nread - 1] = '\0';

    return (line);
}
