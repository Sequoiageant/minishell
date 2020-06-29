#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE		5
# define NB_FLAG		6
# define NB_CONV		10

enum	e_state
{
	LETTER,
	DOLLAR,
	BACKSLASH,
	FLAG,
	PIPE,
	REDIR,
	MULTI
};

typedef struct s_state_machine
{
	enum e_state	state;	
	int				flag_dquote;
	int				flag_quote;
}				t_state_machine;

typedef	int	(*t_function)(char *, t_state_machine *, t_list *);


#endif
