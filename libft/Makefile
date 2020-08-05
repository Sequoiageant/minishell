NAME	=	libft.a

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror

# ---------------- SRC --------------- #

# Main Sources
SRCS += ft_atoi.c
SRCS += ft_lstdelone.c
SRCS += ft_putstr_fd.c
SRCS += ft_strnstr.c
SRCS += ft_bzero.c
SRCS += ft_lstiter.c
SRCS += ft_split.c
SRCS += ft_strrchr.c
SRCS += ft_calloc.c
SRCS += ft_lstlast.c
SRCS += ft_strcat.c
SRCS += ft_strtrim.c
SRCS += ft_inter.c
SRCS += ft_lstmap.c
SRCS += ft_strchr.c
SRCS += ft_substr.c
SRCS += ft_isalnum.c
SRCS += ft_lstnew.c
SRCS += ft_strcmp.c
SRCS += ft_swap_f.c
SRCS += ft_isalpha.c
SRCS += ft_lstsize.c
SRCS += ft_str_del_1_sur_2.c
SRCS += ft_swap_i.c
SRCS += ft_isascii.c
SRCS += ft_memccpy.c
SRCS += ft_str_delchar.c
SRCS += ft_tolower.c
SRCS += ft_isdigit.c
SRCS += ft_memchr.c
SRCS += ft_strdup.c
SRCS += ft_toupper.c
SRCS += ft_isdigit_str.c
SRCS +=	ft_isalnum_str.c
SRCS += ft_memcmp.c
SRCS += ft_strjoin_back.c
SRCS += ft_isprint.c
SRCS += ft_memcpy.c
SRCS += ft_strjoin.c
SRCS += ft_itoa.c
SRCS += ft_memmove.c
SRCS += ft_strlcat.c
SRCS += ft_itoa_u.c
SRCS += ft_memset.c
SRCS += ft_strlcpy.c
SRCS += ft_lstadd_back.c
SRCS += ft_putchar_fd.c
SRCS += ft_strlen.c
SRCS += ft_lstadd_front.c
SRCS += ft_putendl_fd.c
SRCS += ft_strmapi.c
SRCS += ft_lstclear.c
SRCS += ft_putnbr_fd.c
SRCS += ft_strncmp.c
SRCS += ft_str_free.c
SRCS += ft_split_whitespaces.c
# SRCS += get_next_line_save.c
# SRCS += get_next_line_utils_save.c

vpath %.c ./

# ---------------- INC --------------- #

INCLUDES =	./
HEAD = $(INCLUDES)libft.h

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))


# --------- Compilation Rules -------- #

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $@ $^
			ranlib $(NAME)
			echo "$(yellow)--> Creating $@...$(no_color)"

$(OBJS): 	$(DIR_OBJS)%.o: %.c $(HEAD) Makefile | $(DIR_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

$(DIR_OBJS):
	mkdir -p $@

clean:
			$(RM) -R $(DIR_OBJS)

fclean:		clean
			$(RM) $(NAME)

re: 		fclean
			$(MAKE)

.PHONY:		all clean fclean re
