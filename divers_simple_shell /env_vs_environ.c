#include <stdio.h>

extern char **environ;

int main(int argc, char **argv, char **env)
{
    (void)argc;  // on dit au compilateur qu'on ne se sert pas de argc
    (void)argv;  // idem pour argv

    printf("Address of env (main's 3rd parameter): %p\n", (void *)env);
    printf("Address of environ (global variable):  %p\n", (void *)environ);

    if (env == environ)
        printf("They are the SAME!\n");
    else
        printf("They are DIFFERENT!\n");

    return 0;
}
