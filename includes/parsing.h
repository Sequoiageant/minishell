/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:10 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 11:06:34 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_SPLIT_BUF	5
# define NB_SPLIT_CMD	8
# define NB_LEXER		5
# define NB_CLEANER		4

# define REDIR_OUT		1
# define REDIR_APPEND	2
# define REDIR_IN		3

# define REDIR	1
# define ARGV	2

# define ON		1
# define OFF	0

# define SPACE	32
# define TAB	9

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
	char	*original;
}				t_redir;

/*
** ------------------------------- FSM LEXER ------------------------------
*/

enum	e_state_lexer
{
	L_LETTER,
	L_BACKSLASH,
	L_FLAG,
	L_CHECK_APRES,
	L_CHECK_AVANT
};

typedef struct	s_fsm_lexer
{
	enum e_state_lexer	state;
	int					flag_dquote;
	int					flag_quote;
}				t_fsm_lexer;

typedef	int	(*t_func_lex)(t_fsm_lexer *, char *, int);

/*
** ------------------------------- FSM SPLIT_BUF ------------------------------
*/

enum	e_state
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
** ------------------------------- FSM SPLIT_CMD ------------------------------
*/

enum	e_state_split
{
	SP_LETTER,
	SP_BACKSLASH,
	SP_FLAG_QUOTE,
	SP_FLAG_DQUOTE,
	SP_REDIR_ON,
	SP_REDIR_OFF,
	SP_WHITESPACE,
	SP_DOLLAR
};

typedef struct	s_fsm_cmd
{
	int					state;
	int					flag_dquote;
	int					flag_quote;
	int					flag_redir;
}				t_fsm_cmd;

typedef	int	(*t_func_split)(t_fsm_cmd *, char *buf, t_cmd *cmd);

/*
** ------------------------------- FSM Clean ------------------------------
*/

enum	e_state_clean
{
	CL_LETTER,
	CL_BACKSLASH,
	CL_FLAG_QUOTE,
	CL_FLAG_DQUOTE
};

typedef	int	(*t_func_clean)(t_fsm_cmd *, char *buf, char **clean_str);

/*
** ------------------------------- LEXER ------------------------------
*/

int				lexer(char *buf);
int				lex_check_apres(t_fsm_lexer *m, char *buf, int i);
int				lex_check_avant(t_fsm_lexer *m, char *buf, int i);
int				lex_flag(t_fsm_lexer *m, char *buf, int i);
int				lex_letter(t_fsm_lexer *m, char *buf, int i);
int				lex_backslash(t_fsm_lexer *m, char *buf, int i);

/*
** ------------------------------- SPLIT BUF ------------------------------
*/

int				fsm_dollar(char *b, t_state_machine *m, t_list *e, t_list **p);
int				fsm_backsl(char *b, t_state_machine *m, t_list *e, t_list **p);
int				fsm_flag(char *b, t_state_machine *m, t_list *e, t_list **p);
int				fsm_letter(char *b, t_state_machine *m, t_list *e, t_list **p);
int				fsm_multi(char *b, t_state_machine *m, t_list *e, t_list **p);
int				fsm_pipe(char *b, t_state_machine *m, t_list *e, t_list **p);

int				parser_split_buf(char *buf, t_list *env, t_list **pipe_list);
int				add_pipe(t_list **pipe_list);
int				add_cmd(t_list *pipe_list);
void			ft_init_cmd(t_cmd *cmd);
int				ft_join_to_cmd_buf(char *str, t_list *pipe_list);
void			delete_bn(char **str);

/*
** ------------------------------- SPLIT CMD ------------------------------
*/

int				parser_split_cmd(t_cmd *cmd);

int				sp_backslash(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int				sp_flag_quote(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int				sp_flag_dquote(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int				sp_flag_redir_on(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int				sp_flag_redir_off(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int				sp_letter(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int				sp_whitespace(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int				sp_dollar(t_fsm_cmd *m, char *buf, t_cmd *cmd);

int				ft_join_to_redir(char *added_str, t_list *redir_list);
int				ft_join_to_argv(char *added_str, t_cmd *cmd);
int				set_redir_state(char *buf, int *state);
int				ft_set_env_flag(t_cmd *cmd, int val, int where);

/*
** ------------------------------- CLEAN ------------------------------
*/

int				clean_quotes(t_list *cmd_list);
int				cl_letter(t_fsm_cmd *m, char *buf, char **cleaned);
int				cl_flag_quote(t_fsm_cmd *m, char *buf, char **cleaned);
int				cl_flag_dquote(t_fsm_cmd *m, char *buf, char **cleaned);
int				cl_backslash(t_fsm_cmd *m, char *buf, char **cleaned);

/*
** ------------------------------- UTILS ------------------------------
*/

int				ft_parse(char *buf, t_list *env, t_list **pipe_list);

char			*char_to_str(char c);
int				ft_is_special(char c);
int				ft_join_to_str(char *added_str, char **initial_str);
int				ft_is_dollar_start(char c);
size_t			count_dollar_char(char *buf);

int				fill_cmdlist_path(t_list *cmd_list, t_list *env);
char			**ft_list_to_tab_argv(t_list *argv);

#endif
