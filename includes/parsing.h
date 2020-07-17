/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:10 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 11:21:31 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE		7
# define NB_FLAG		6
# define NB_CONV		10

typedef struct	s_cmd
{
	char	*buf;
	char	**argv;
	int		argc;
	int		output_file;
	int		output_file_append;
	int		input_file;
	char	*file;
	char	*cmd_path;
}				t_cmd;

enum			e_state
{
	LETTER,
	DOLLAR,
	BACKSLASH,
	FLAG,
	MULTI,
	PIPE,
	REDIR
};

typedef struct	s_state_machine
{
	enum e_state	state;
	int				flag_dquote;
	int				flag_quote;
}				t_state_machine;

typedef	int	(*t_function)(char *, t_state_machine *, t_list *, t_list **);

int		fsm_dollar(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_backslash(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_flag(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_letter(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_multi(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_pipe(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_redir(char *buf, t_state_machine *m, t_list *env, t_list **p);

int		ft_parse(char *buf, t_list *env, t_list **pipe_list);
int		add_pipe(t_list **pipe_list);
int		add_cmd(t_list *pipe_list);
void	ft_init_cmd(t_cmd *cmd);
int		ft_join_to_cmd_buf(char *str, t_list *pipe_list);
char	*char_to_str(char c);
int		ft_is_special(char c);
int		filler(t_list *pipe_list, t_list *env);
int		contains_redir(char *buf);
int		fill_redir(t_cmd *cmd);
int		fill_argv(t_cmd *cmd);
int		fill_cmd_path(t_cmd *cmd, t_list *env);
void	print_commands(t_list *pipe_list);

#endif