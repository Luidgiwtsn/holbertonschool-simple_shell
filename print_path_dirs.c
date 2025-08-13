#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * @name: Nom de la variable (ex : "PATH")
 *
 * Return: Pointeur vers la valeur de la variable, ou NULL si non trouvée
 */
char *_getenv(const char *name)
{
	int i = 0;
	int j;

	if (name == NULL)
		return (NULL);

	while (environ[i])
	{
		j = 0;
		while (name[j] && environ[i][j] == name[j])
			j++;

		if (name[j] == '\0' && environ[i][j] == '=')
			return (&environ[i][j + 1]);

		i++;
	}
	return (NULL);
}

/**
 * print_path_dirs - Affiche chaque dossier contenu dans la variable PATH
 *
 * Cette fonction récupère la variable PATH, puis affiche
 * chaque dossier (séparé par :) sur une ligne différente.
 */
void print_path_dirs(void)
{
	char *path, *path_copy, *token;

	path = _getenv("PATH");
	if (path == NULL)
	{
		printf("La variable PATH n'existe pas.\n");
		return;
	}

	/* Crée une copie modifiable de PATH */
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("Erreur d'allocation");
		return;
	}

	/* Découpe la chaîne selon le caractère ':' */
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}

	free(path_copy);
}