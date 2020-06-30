/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:02 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/29 19:13:12 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHINE_H
# define MACHINE_H

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0


# define NB_STATE	5
# define NB_SUBST	3

# define MACHINE_ERROR		-1
# define MACHINE_CONTINUE	1
# define MACHINE_AGAIN		0


# define LETTER_SPECIAL	"\"\'\\$~?"
# define SUBST_STR		"\"\'\\"
# define BACKSLASH		"\\"
# define QUOTES 		"'"
# define DB_QUOTES		"\""
# define PIPE			"|"
# define SEMICOLON		";"
# define GREAT			">"
# define LESS			"<"
# define GREAT_END		">>"
# define DOLLAR			"$"
# define INTER_PT		"?"

enum			e_state
{
	LETTER,
	SUBST,
	OPERATOR,
	ERROR
};

typedef struct		s_state_machine
{
	enum e_state	state;
	int				error;
	short			subst;
	short			backslash;
}					t_stm;


typedef	int			(*t_func2)(char *, t_list *, t_stm *);

#endif