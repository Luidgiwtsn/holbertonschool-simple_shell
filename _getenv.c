#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Déclaration externe d'environ */
extern char **environ;

/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * @name: Le nom de la variable d'environnement à chercher
 *
 * Description: Cette fonction parcourt les variables d'environnement
 * pour trouver une variable avec le nom donné et retourne sa valeur.
 * L'environnement est accessible via la variable globale environ.
 *
 * Return: Pointeur vers la chaîne de valeur si trouvée, NULL sinon
 */
char *_getenv(const char *name)
{
    int i;
    size_t name_len;
    char *var_env, *pos_egal;

    /* Vérifier si name est NULL ou vide */
    if (name == NULL || *name == '\0')
        return (NULL);

    /* Obtenir la longueur du nom de la variable */
    name_len = strlen(name);

    /* Parcourir les variables d'environnement */
    for (i = 0; environ[i] != NULL; i++)
    {
        var_env = environ[i];
        
        /* Trouver le caractère '=' dans la variable d'environnement */
        pos_egal = strchr(var_env, '=');
        
        /* Ignorer si aucun '=' trouvé (entrée mal formée) */
        if (pos_egal == NULL)
            continue;
        
        /* Vérifier si la longueur du nom correspond et que le nom correspond */
         if ((size_t)(pos_egal - var_env) == name_len &&
            strncmp(var_env, name, name_len) == 0)
        {
            /* Retourner un pointeur vers la valeur (après '=') */
            return (pos_egal + 1);
        }
    }

    /* Variable non trouvée */
    return (NULL);
}

/* Fonction de test pour démontrer l'utilisation */
int main(void)
{
    char *valeur;
    
    printf("Test de la fonction _getenv :\n\n");
    
    /* Tester avec quelques variables d'environnement courantes */
    valeur = _getenv("PATH");
    if (valeur)
        printf("PATH = %s\n\n", valeur);
    else
        printf("PATH non trouvé\n\n");
    
    valeur = _getenv("HOME");
    if (valeur)
        printf("HOME = %s\n\n", valeur);
    else
        printf("HOME non trouvé\n\n");
    
    valeur = _getenv("USER");
    if (valeur)
        printf("USER = %s\n\n", valeur);
    else
        printf("USER non trouvé\n\n");
    
    /* Tester avec une variable inexistante */
    valeur = _getenv("VARIABLE_INEXISTANTE");
    if (valeur)
        printf("VARIABLE_INEXISTANTE = %s\n\n", valeur);
    else
        printf("VARIABLE_INEXISTANTE non trouvée\n\n");
    
    /* Tester avec une entrée NULL */
    valeur = _getenv(NULL);
    if (valeur)
        printf("Test NULL = %s\n", valeur);
    else
        printf("Entrée NULL a correctement retourné NULL\n");
    
    return (0);
}
