#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_ARGS 64

extern char **environ;

/* Tokenisation simple avec strtok */
char **tokenize(char *line) {
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    if (!args) return NULL;

    int i = 0;
    char *token = strtok(line, " \t");
    while (token && i < MAX_ARGS - 1) {
        args[i] = strdup(token);
        if (!args[i]) {
            for (int j = 0; j < i; j++) free(args[j]);
            free(args);
            return NULL;
        }
        token = strtok(NULL, " \t");
        i++;
    }
    args[i] = NULL;
    return args;
}

/* Affiche les variables d’environnement */
void print_env(void) {
    for (int i = 0; environ[i]; i++) {
        printf("%s\n", environ[i]);
    }
}

/* Recherche le chemin complet d’un binaire dans le PATH */
char *find_command(char *cmd) {
    if (access(cmd, X_OK) == 0) return strdup(cmd);

    char *path = getenv("PATH");
    if (!path) return NULL;

    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");
    while (dir) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

int main(void) {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        if (isatty(STDIN_FILENO)) {
            printf("myshell$ ");
        }

        if (getline(&line, &len, stdin) == -1) {
            if (feof(stdin)) break;
            perror("getline");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0) {
            break;
        }

        if (strcmp(line, "env") == 0) {
            print_env();
            continue;
        }

        char **args = tokenize(line);
        if (!args || !args[0]) {
            free(args);
            continue;
        }

        char *cmd_path = find_command(args[0]);
        if (!cmd_path) {
            fprintf(stderr, "myshell: command not found: %s\n", args[0]);
            for (int i = 0; args[i]; i++) free(args[i]);
            free(args);
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            execve(cmd_path, args, environ);
            fprintf(stderr, "myshell: exec error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork");
        }

        free(cmd_path);
        for (int i = 0; args[i]; i++) free(args[i]);
        free(args);
    }

    free(line);
    return 0;
}
