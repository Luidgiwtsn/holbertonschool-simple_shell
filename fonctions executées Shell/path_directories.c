#include "main.h"

/**
 * _getenv - Retrieves the value of the environment variable specified by name.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: Pointer to the value string, or NULL if not found.
 */
char *_getenv(const char *name)
{
    extern char **environ;
    int name_len = strlen(name);
    
    for (int i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            return environ[i] + name_len + 1;
        }
    }
    return NULL;
}

/* Fonction pour créer un nouveau nœud */
PathNode *create_node(const char *directory)
{
    PathNode *node = malloc(sizeof(PathNode));
    if (!node) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    
    node->directory = malloc(strlen(directory) + 1);
    if (!node->directory) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le répertoire\n");
        free(node);
        return NULL;
    }
    
    strcpy(node->directory, directory);
    node->next = NULL;
    return node;
}

/* Fonction principale pour parser PATH et construire la liste chaînée */
PathNode *parse_path(const char *path_env)
{
    if (!path_env) {
        return NULL;
    }
    
    /* Copier PATH car strtok modifie la chaîne */
    char *path_copy = malloc(strlen(path_env) + 1);
    if (!path_copy) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    strcpy(path_copy, path_env);
    
    PathNode *head = NULL;
    PathNode *tail = NULL;
    
    /* Séparer les répertoires avec ':' */
    char *token = strtok(path_copy, ":");
    while (token != NULL) {
        /* Ignorer les entrées vides */
        if (strlen(token) > 0) {
            PathNode *new_node = create_node(token);
            if (!new_node) {
                /* Nettoyer en cas d'erreur */
                free(path_copy);
                free_path_list(head);
                return NULL;
            }
            
            if (!head) {
                head = tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
        token = strtok(NULL, ":");
    }
    
    free(path_copy);
    return head;
}

/* Fonction pour libérer la mémoire de la liste chaînée */
void free_path_list(PathNode *head)
{
    PathNode *current = head;
    while (current) {
        PathNode *next = current->next;
        free(current->directory);
        free(current);
        current = next;
    }
}

/* Fonction pour afficher la liste */
void print_path_list(PathNode *head)
{
    PathNode *current = head;
    int count = 1;
    
    printf("Répertoires PATH :\n");
    while (current) {
        printf("%d. %s\n", count++, current->directory);
        current = current->next;
    }
}

/* Fonction pour compter les répertoires */
int count_directories(PathNode *head)
{
    int count = 0;
    PathNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/* Fonction principale pour construire la liste des répertoires PATH */
PathNode *build_path_list(void)
{
    char *path_env = _getenv("PATH");
    if (!path_env) {
        fprintf(stderr, "Variable PATH non trouvée\n");
        return NULL;
    }
    
    return parse_path(path_env);
}

/* Exemple d'utilisation */
int main(void)
{
    PathNode *path_list = build_path_list();
    
    if (path_list) {
        print_path_list(path_list);
        printf("\nNombre total de répertoires : %d\n", count_directories(path_list));
        
    /* Libérer la mémoire */
    free_path_list(path_list);
    } else {
    printf("Impossible de construire la liste PATH\n");
    return 1;
    }
    return 0;
}
