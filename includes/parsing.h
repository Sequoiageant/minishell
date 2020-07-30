/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:10 by grim              #+#    #+#             */
/*   Updated: 2020/07/30 15:06:15 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE		5
# define NB_STATE_REDIR	9
# define NB_STATE_LEX	5

# define REDIR_OUT		1
# define REDIR_APPEND	2
# define REDIR_IN		3

#define REDIR	1
#define ARGV	2

#define ON		1
#define OFF		0

#define SPACE	32
#define TAB		9

typedef struct	s_cmd
{
	char	*buf;
	char	*cmd_path;
	char	**argv;
	int		argc;
	char	pad[4];
	t_list	*redir;
	t_list	*argv_list;
	t_list	*flag;
	t_list	*flag_redir;
}				t_cmd;

typedef struct	s_redir
{
	int		state;
	char	pad[4];
	char	*file;
	char	*original; //nom du fichier avant substitution (pour les cas de ambiguous redir)
}				t_redir;

/*
** ------------------------------- FSM LEXER ------------------------------
*/

enum			e_state_lexer
{
	L_LETTER,
	L_BACKSLASH,
	L_FLAG,
	L_CHECK_APRES,
	L_CHECK_AVANT,
};

typedef struct	s_fsm_lexer
{
	enum e_state_lexer	state;
	int					flag_dquote;
	int					flag_quote;
}				t_fsm_lexer;

typedef	int	(*t_func_lex)(t_fsm_lexer *, char *, int);

/*
** ------------------------------- FSM PARSING ------------------------------
*/

enum			e_state
{
	LETTER,
	BACKSLASH,
	FLAG,
	MULTI,
	PIPE
};

typedef struct	s_state_machine
{
	enum e_state	state;
	int				flag_dquote;
	int				flag_quote;
}				t_state_machine;

typedef	int	(*t_function)(char *, t_state_machine *, t_list *, t_list **);

/*
** ------------------------------- FSM PARSING_REDIR ------------------------------
*/

enum			e_state_redir
{
	R_LETTER,
	R_BACKSLASH,
	R_FLAG_QUOTE,
	R_FLAG_DQUOTE,
	R_FLAG_REDIR_ON,
	R_FLAG_REDIR_OFF,
	R_DOLLAR,
	R_WHITESPACE
};

typedef struct	s_fms_redir
{
	enum e_state_redir	state;
	int					flag_dquote;
	int					flag_quote;
	int					flag_redir;
}				t_fsm_redir;

typedef	int	(*t_func_redir)(t_fsm_redir *, char *, t_cmd *);

/*
** ------------------------------- Lexer ------------------------------
*/

int		lexer(char *buf);
int		lex_check_apres(t_fsm_lexer *m, char *buf, int i);
int		lex_check_avant(t_fsm_lexer *m, char *buf, int i);
int		lex_flag(t_fsm_lexer *m, char *buf, int i);
int		lex_letter(t_fsm_lexer *m, char *buf, int i);
int		lex_backslash(t_fsm_lexer *m, char *buf, int i);

/*
** ------------------------------- Parser ------------------------------
*/

int		fsm_dollar(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_backslash(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_flag(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_letter(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_multi(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_pipe(char *buf, t_state_machine *m, t_list *env, t_list **p);

int		ft_parse(char *buf, t_list *env, t_list **pipe_list);
int		add_pipe(t_list **pipe_list);
int		add_cmd(t_list *pipe_list);
void	ft_init_cmd(t_cmd *cmd);
char	*char_to_str(char c);
int		ft_join_to_cmd_buf(char *str, t_list *pipe_list);
int		ft_is_dollar_start(char c);
int		count_dollar_char(char *buf);
int		ft_is_special(char c);

/*
** ------------------------------- Parser Redir ------------------------------
*/

int		red_backslash(t_fsm_redir *m, char *buf, t_cmd *cmd);
int		red_flag_quote(t_fsm_redir *m, char *buf, t_cmd *cmd);
int		red_flag_dquote(t_fsm_redir *m, char *buf, t_cmd *cmd);
int		red_flag_redir_on(t_fsm_redir *m, char *buf, t_cmd *cmd);
int		red_flag_redir_off(t_fsm_redir *m, char *buf, t_cmd *cmd);
int		red_letter(t_fsm_redir *m, char *buf, t_cmd *cmd);
int		red_dollar(t_fsm_redir *m, char *buf, t_cmd *cmd);
int		red_whitespace(t_fsm_redir *m, char *buf, t_cmd *cmd);

int		parser_redir(t_list *pipe_list);
int		ft_join_to_redir(char *added_str, t_list *redir_list);
int		ft_join_to_str(char *added_str, char **initial_str);
int		set_redir_state(char *buf, int *state);
int		ft_set_env_flag(t_cmd *cmd, int val, int where);
int		ft_join_to_argv(char *added_str, t_cmd *cmd);

/*
** ------------------------------- Filler ------------------------------
*/

int		filler(t_list *pipe_list, t_list *env);
int		contains_redir(char *buf);
int		fill_redir(t_cmd *cmd);
int		fill_argv(t_cmd *cmd);
int		fill_cmd_path(t_cmd *cmd, t_list *env);
void	print_commands(t_list *pipe_list);
char	**ft_list_to_tab_argv(t_list *argv);


#endif
