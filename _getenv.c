#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


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


    if (name == NULL || *name == '\0')
        return (NULL);


        name_len = strlen(name);


    for (i = 0; environ[i] != NULL; i++)
    {
        var_env = environ[i];
        

        pos_egal = strchr(var_env, '=');
        

        if (pos_egal == NULL)
            continue;
        

        
         if ((size_t)(pos_egal - var_env) == name_len &&
            strncmp(var_env, name, name_len) == 0)

            {
            return (pos_egal + 1);
        }
    }

    return (NULL);
    
}

