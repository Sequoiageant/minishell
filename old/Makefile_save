SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
FLAGS = -Werror -Wextra -Wall
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	cd libft ; make
	gcc $(OBJ) -o $(NAME) -Llibft -lft

%.o: %.c
	gcc -c -g $(FLAGS) $^ -o $@

clean:
	cd libft ; make clean
	rm -f $(OBJ)

fclean: clean
	cd libft ; make fclean
	rm -f $(NAME)

re: fclean all