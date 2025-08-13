#include <stdio.h>

char *_getenv(const char *name);

/**
 * main - Teste la fonction _getenv
 *
 * Return: 0 si succès
 */
int main(void)
{
	char *valeur;

	valeur = _getenv("PATH");

	if (valeur != NULL)
		printf("PATH = %s\n", valeur);
	else
		printf("Variable non trouvée.\n");

	return (0);
}