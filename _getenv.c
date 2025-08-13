#include <stdio.h>
#include <string.h>

extern char **environ;

/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * sans utiliser la fonction standard getenv.
 * @name: Nom de la variable d'environnement à rechercher
 *
 * Return: Pointeur vers la valeur de la variable, ou NULL si non trouvée.
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = 0;

	if (name == NULL)
		return (NULL);

	len = strlen(name);

	while (environ[i] != NULL)
	{
		/* Vérifie si le nom correspond et est suivi d'un '=' */
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]);
		}
		i++;
	}

	return (NULL);
}