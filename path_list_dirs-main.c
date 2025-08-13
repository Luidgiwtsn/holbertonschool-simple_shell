#include <stdio.h>
#include <stdlib.h>

typedef struct path_node
{
	char *dir;
	struct path_node *next;
} path_node;

path_node *build_path_list(void);

/**
 * print_path_list - Affiche tous les dossiers de la liste PATH
 * @head: Pointeur vers le début de la liste
 */
void print_path_list(path_node *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->dir);
		head = head->next;
	}
}

/**
 * free_path_list - Libère toute la mémoire utilisée par la liste
 * @head: Pointeur vers le début de la liste
 */
void free_path_list(path_node *head)
{
	path_node *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->dir);
		free(tmp);
	}
}

/**
 * main - Point d'entrée du programme
 *
 * Return: 0 si succès
 */
int main(void)
{
	path_node *list = build_path_list();

	if (list == NULL)
	{
		printf("Erreur lors de la création de la liste PATH.\n");
		return (1);
	}

	print_path_list(list);
	free_path_list(list);

	return (0);
}