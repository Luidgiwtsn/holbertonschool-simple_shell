#include <stdio.h>

/**
 * main - Affiche l'adresse de 'env' et 'environ'
 * @argc: Nombre d'arguments
 * @argv: Tableau des arguments
 * @env: Tableau des variables d'environnement
 *
 * Return: 0 en cas de succès
 */

int main(int argc, char *argv[], char *env[])
{
	extern char **environ;

	(void)argc;
	(void)argv;

	printf("Adresse de 'env' (paramètre de main)     : %p\n", (void *)env);
	printf("Adresse de 'environ' (variable globale)   : %p\n", (void *)environ);

	return (0);
}