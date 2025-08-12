#include <stdio.h>

/* Declare the global environ variable */
extern char **environ;

/**
 * main - Prints the environment variables
 *
 * Return: Always 0.
 */
int main(void)
{
    int i = 0;

    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }

    return (0);
}