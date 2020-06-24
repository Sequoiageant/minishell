SRC = $(wildcard *.c)

OBJ = $(SRC:%.c=%.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc libft.a $(OBJ)

%.o: %.c
	gcc -c -Wall -Werror -Wextra $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
