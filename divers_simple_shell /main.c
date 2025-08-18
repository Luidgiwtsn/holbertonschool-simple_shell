#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
int main(void)
{
    printf("Avant modification :\n");
    print_environ(); // suppose que tu as cette fonction

    _setenv("MY_VAR", "HelloWorld", 1);

    printf("\nAprès modification :\n");
    print_environ();

    return 0;
}
