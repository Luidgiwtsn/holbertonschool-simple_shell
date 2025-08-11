#include <stdio.h>

int main(int __attribute__((unused)) ac, char **av)
{
    int i = 0;

    while (av[i] != NULL)
    {
        printf("Argument %d: %s\n", i, av[i]);
        i++;
    }

        printf("The total number of arguments (including the program name) : %d\n", i);

    return 0;
}