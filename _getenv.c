#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

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

