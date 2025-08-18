# Nom de l'exécutable
NAME = hsh

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

# Fichiers sources
SRC = execve_hsh.c free_args_hsh.c prompt_hsh.c strtok_hsh.c _getenv.c hsh.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Règle principale : création de l'exécutable
$(NAME): $(OBJ)
    $(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Compilation de chaque fichier .c en .o
%.o: %.c main.h
    $(CC) $(CFLAGS) -c $< -o $@
