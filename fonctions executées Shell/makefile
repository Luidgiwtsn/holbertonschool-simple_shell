NAME = hsh
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
SRC = execve_hsh.c free_args_hsh.c prompt_hsh.c strtok_hsh.c _getenv.c main.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
    $(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c main.h
    $(CC) $(CFLAGS) -c $< -o $@
