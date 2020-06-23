SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
FLAGS = -Werror -Wextra -Wall
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) -L. -lft

%.o: %.c
	gcc -c -g $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all