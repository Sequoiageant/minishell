/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:10 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 11:51:10 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "libft.h"

// buffer = une ou plusieurs pipelines
// pipeline = une ou plusieurs commandes


// cmd 1 ; cmd2 | cmd 3 | cmd4 ; cmd5
// 3 pipeline avec 1 cmd, 3 cmd, 1 cmd


// t_list  *pipeline_list

// pipeline_list->content = (t_pipeline *)pipeline
// pipeline_list->next = autre t_pipeline


# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE		5
# define NB_FLAG		6
# define NB_CONV		10

typedef struct	s_pipeline
{
    t_list      *cmd_list;
    char        *pipe_buf;
}				t_pipeline;

// cmd->content = (t_cmd*)cmd;

typedef struct s_cmd
{
    char        *buf;
    char		**argv;
	int		    argc;
    int         output_file; // >
    int         output_file_append; // >>
    int         input_file; // <
    char        *file; // pour >, >> et <
}               t_cmd;

enum	e_state
{
	LETTER,
	DOLLAR,
	BACKSLASH,
	FLAG,
	MULTI,
    PIPE
};

typedef struct s_state_machine
{
	enum e_state	state;	
	int				flag_dquote;
	int				flag_quote;
}				t_state_machine;

typedef	int	(*t_function)(char *, t_state_machine *, t_list *, t_list **);

int		dollar(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list);
int		backslash(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list);
int		flag(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list);
int		letter(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list);
int		multi(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list);

int     ft_parse(char *buf, t_list *env, t_list **pipe_list);
int		add_pipe(t_list **pipe_list);
int     ft_join_str_to_pipe(char *str, t_list *pipe_list);
char    *char_to_str(char c);
int		ft_is_special(char c);

#endif