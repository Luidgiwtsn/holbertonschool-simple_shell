#include <stdio.h>

int main(int __attribute__((unused)) ac, char **av)
{
    int i = 0;

    while (av[i] != NULL)
    {
        printf("Argument %d: %s\n", i, av[i]);
        i++;
    }

    printf("Nombre total d'arguments (y compris le nom du programme) : %d\n", i);

    return 0;
}
