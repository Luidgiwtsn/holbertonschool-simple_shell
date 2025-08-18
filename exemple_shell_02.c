#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;//déclaration de la variable d'environnement globaleo

int main(void)
{
    char *line = NULL;// Pointeur pour stocker la ligne lue
    size_t len = 0; //type size_t pour la taille de la ligne // unsigned donc que positif
    ssize_t nread; // ssize_t pour la taille lue, peut être négatif en cas d'erreur >0 ok -1 probleme avantage avec type signé
    pid_t pid; // identifiant de processus (= 0 pour le processus enfant)(-1 pour l'erreur)(>0 pour le processus parent)

    while (1)
    {
        if (isatty(STDIN_FILENO)) // = Descripteur de fichier = 0 /vérifie si l'entrée standard est un terminal si oui 1 si non = 0
            printf("#cisfun$ ");

        nread = getline(&line, &len, stdin);		//getline lit une ligne depuis l'entrée standard et stocke dans line, len est la taille allouée pour line stdin
        if (nread == -1)        // si getline retourne -1, cela signifie qu'il y a eu une erreur ou que l'utilisateur a entré Ctrl+D (EOF)
        {
            free(line);//libère la mémoire allouée pour line
            break;  // Ctrl+D ou erreur de lecture
        }

        line[strcspn(line, "\n")] = '\0';  // Supprime le \n et remplace par \0 pour terminer la chaîne de caractères
					// on aurait pu utiliser strtok ou ? mais trop risque / destructeur
        if (strcmp(line, "exit") == 0)// compare la ligne entrée avec "exit"
            break;// Si l'utilisateur entre "exit", on quitte la boucle

        if (strlen(line) == 0) // verifie si la ligne est vide
            continue;  // Ligne vide

			char *line_copy = strdup(line); // copie de la ligne pour ne pas la modifier directement
			if (line_copy == NULL) 
			{
				perror("copie ratée strdup");
				continue; // passe à la prochaine itération en cas d'erreur
			}
		// decoupage de la ligne en argument

		char *args[100]; // tableau pour stocker les arguments j ai vu largement
		int i = 0;
		char *token = strtok(line, " "); 
		while (token != NULL && i < 99) // limite de 99 pour éviter le débordement
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL; // termine le tableau d'arguments avec NULL			
			
			// decoupe la ligne en tokens en utilisant l'espace comme séparateur
        pid = fork();// clone le processus courant, créant un nouveau processus enfant
		if (pid < 0) 
		{ 
			perror("fork");
			continue;
		}// si fork échoue, pid est négatif
        else if (pid == 0) // si on est dans le processus enfant alors == 0
        // enfant 
		{
            execve(args[0], args, environ); // exécute la commande entrée par l'utilisateur, args[0] est le nom de la commande, args est le tableau d'arguments et environ est la variable d'environnement
			perror("execve"); // si execve échoue, on affiche une erreur
            perror("./shell"); // affiche le nom du programme qui a échoué
            exit(EXIT_FAILURE); // termine le processus enfant avec un code d'erreur
        }
        else if (pid > 0) // si on est dans le processus parent alors > 0
        {
            wait(NULL); // attend que le processus enfant se termine
        }
        else
        {
            perror("fork"); // si fork échoue, on affiche une erreur
        }
    }

    free(line); // libère la mémoire allouée pour line
    return 0;// termine le programme avec succès
}

