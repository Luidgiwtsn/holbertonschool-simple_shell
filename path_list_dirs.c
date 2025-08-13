#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * struct path_node - Représente un dossier dans la liste chaînée
 * @dir: Le chemin du dossier (chaîne de caractères)
 * @next: Pointeur vers le prochain nœud
 */
typedef struct path_node
{
	char *dir;
	struct path_node *next;
} path_node;

/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * @name: Nom de la variable (ex: "PATH")
 *
 * Return: Pointeur vers la valeur de la variable, ou NULL si non trouvée
 */
char *_getenv(const char *name)
{
	int i = 0, j;

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
 * build_path_list - Construit une liste chaînée des dossiers du PATH
 *
 * Return: Pointeur vers le premier nœud de la liste, ou NULL si erreur
 */
path_node *build_path_list(void)
{
	char *path, *path_copy, *token;
	path_node *head = NULL, *new_node;
	path_node *last = NULL;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		new_node = malloc(sizeof(path_node));
		if (new_node == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		new_node->dir = strdup(token);
		if (new_node->dir == NULL)
		{
			free(new_node);
			free(path_copy);
			return (NULL);
		}
		new_node->next = NULL;

		if (head == NULL)
			head = new_node;
		else
			last->next = new_node;

		last = new_node;
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (head);
}