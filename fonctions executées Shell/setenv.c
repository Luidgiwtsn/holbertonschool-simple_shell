#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite) {
    if (!name || !*name || strchr(name, '=')) {
        // Nom invalide
        return -1;
    }

    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    size_t total_len = name_len + value_len + 2; // +1 pour '=' et +1 pour '\0'

    char *new_var = malloc(total_len);
    if (!new_var) return -1;

    sprintf(new_var, "%s=%s", name, value);

    for (int i = 0; environ[i]; i++) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            if (!overwrite) {
                free(new_var);
                return 0;
            }
            environ[i] = new_var;
            return 0;
        }
    	if (environ[i] == NULL) {
			environ[i] = new_var;
			environ[i + 1] = NULL; // Terminate the array
			return 0;
		}
	}

	// Si on arrive ici, on n'a pas trouvé la variable, on l'ajoute à la fin
	int i;
	for (i = 0; environ[i] != NULL; i++);
	
	environ[i] = new_var;
	environ[i + 1] = NULL; // Terminate the array

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

// Déclaration de la fonction
int _setenv(const char *name, const char *value, int overwrite);

int main(void) {
    // Test de la fonction
    if (_setenv("MON_VAR", "Bonjour", 1) == 0) {
        printf("Variable ajoutée/modifiée avec succès.\n");
        printf("MON_VAR = %s\n", getenv("MON_VAR"));
    } else {
        printf("Erreur lors de l'ajout/modification de la variable.\n");
    }

    return 0;
}
