#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_string - Splits a string into words using multiple delimiters
 * @str: the input string to split
 * @count: pointer to an int to store the number of words found
 *
 * Return: an array of strings (words), or NULL on failure
 */
char **split_string(const char *str, int *count)
{
	char *copy, *token;
	const char *delimiters = " ,.;\n\t\r";
	int capacity = 10, i = 0;
	char **result;

	if (str == NULL || count == NULL)
		return (NULL);

	copy = strdup(str);
	if (copy == NULL)
		return (NULL);

	result = malloc(capacity * sizeof(char *));
	if (result == NULL)
	{
		free(copy);
		return (NULL);
	}

	token = strtok(copy, delimiters);
	while (token != NULL)
	{
		if (i >= capacity)
		{
			capacity *= 2;
			result = realloc(result, capacity * sizeof(char *));
			if (result == NULL)
			{
				free(copy);
				return (NULL);
			}
		}
		result[i] = strdup(token);
		if (result[i] == NULL)
		{
			free(copy);
			return (NULL);
		}
		i++;
		token = strtok(NULL, delimiters);
	}

	*count = i;
	free(copy);
	return (result);
}

int main(void)
{
    char line[] = "ls -l /home/user";
    int count;
    char **args = split_string(line, &count);

    if (args == NULL)
    {
        printf("Error splitting string\n");
        return (1);
    }

    for (int i = 0; i < count; i++)
    {
        printf("arg[%d]: %s\n", i, args[i]);
        free(args[i]);  // libération de chaque mot
    }
    free(args);  // libération du tableau

    return (0);
}