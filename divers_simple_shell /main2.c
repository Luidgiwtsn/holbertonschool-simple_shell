#include <stdio.h>    // pour printf
#include <stdlib.h>   // pour getenv

/* Prototype de notre fonction */
int _unsetenv(const char *name);



int main(void)
{
    printf("Before unset: %s\n", getenv("HOME"));

    _unsetenv("HOME");

    printf("After unset: %s\n", getenv("HOME")); // Should print (null)

    return 0;
}
