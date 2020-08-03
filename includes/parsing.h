/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:10 by grim              #+#    #+#             */
/*   Updated: 2020/08/03 15:53:47 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "mshell.h"

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE_MULTI	5
# define NB_STATE_SUBST	5
# define NB_STATE_SPLIT	8
# define NB_STATE_LEX	5
# define NB_STATE_CLEAN	4

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
** ------------------------------- FSM MULTI ------------------------------
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
** ------------------------------- FSM SUBST & FSM WHITESPACE ------------------------------
*/

enum			e_state_subst
{
	SU_LETTER,
	SU_BACKSLASH,
	SU_FLAG_QUOTE,
	SU_FLAG_DQUOTE,
	SU_SUBST
};

enum			e_state_split
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

typedef	int	(*t_func_subst)(t_fsm_cmd *, char *buf, t_cmd *cmd, t_list *env);
typedef	int	(*t_func_split)(t_fsm_cmd *, char *buf, t_cmd *cmd);

/*
** ------------------------------- FSM Clean ------------------------------
*/

enum			e_state_clean
{
	CL_LETTER,
	CL_BACKSLASH,
	CL_FLAG_QUOTE,
	CL_FLAG_DQUOTE,
};

typedef	int	(*t_func_clean)(t_fsm_cmd *, char *buf, char **clean_str);


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
** ------------------------------- Parser MULTI ------------------------------
*/

int		fsm_dollar(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_backslash(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_flag(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_letter(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_multi(char *buf, t_state_machine *m, t_list *env, t_list **p);
int		fsm_pipe(char *buf, t_state_machine *m, t_list *env, t_list **p);

int		add_pipe(t_list **pipe_list);
int		add_cmd(t_list *pipe_list);
void	ft_init_cmd(t_cmd *cmd);
int		ft_join_to_cmd_buf(char *str, t_list *pipe_list);


/*
** ------------------------------- Parser SUBST ------------------------------
*/

int		parse_cmd_subst(t_cmd *cmd, t_list *env);
int		su_backslash(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env);
int		su_flag_quote(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env);
int		su_flag_dquote(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env);
int		su_letter(t_fsm_cmd *m, char *buf, t_cmd *cmd,t_list *env );
int		su_subst(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env );

int		ft_join_to_cmd_buf2(char *str, t_cmd *cmd);
int		ft_is_dollar_start(char c);
int		count_dollar_char(char *buf);

/*
** ------------------------------- Parser SPLIT ------------------------------
*/

int		parse_cmd_split(t_cmd *cmd);
int		sp_backslash(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int		sp_flag_quote(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int		sp_flag_dquote(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int		sp_flag_redir_on(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int		sp_flag_redir_off(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int		sp_letter(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int		sp_whitespace(t_fsm_cmd *m, char *buf, t_cmd *cmd);
int		sp_dollar(t_fsm_cmd *m, char *buf, t_cmd *cmd);

/*
** ------------------------------- Parser CLEAN ------------------------------
*/

int		clean_quotes(t_list *cmd_list);
int		cl_letter(t_fsm_cmd *m, char *buf, char **cleaned);
int		cl_flag_quote(t_fsm_cmd *m, char *buf, char **cleaned);
int		cl_flag_dquote(t_fsm_cmd *m, char *buf, char **cleaned);
int		cl_backslash(t_fsm_cmd *m, char *buf, char **cleaned);

/*
** ------------------------------- OTHER ------------------------------
*/


int		ft_parse(char *buf, t_list *env, t_list **pipe_list);
int		parsing_cmd(t_list *cmd_list, t_list *env);

char	*char_to_str(char c);
int		ft_is_special(char c);
int		ft_join_to_redir(char *added_str, t_list *redir_list);
int		ft_join_to_str(char *added_str, char **initial_str);
int		ft_join_to_argv(char *added_str, t_cmd *cmd);
int		set_redir_state(char *buf, int *state);
int		ft_set_env_flag(t_cmd *cmd, int val, int where);
// int		parser_redir(t_list *pipe_list);

void	print_pipe_list(t_list *pipe_list);
void	print_cmd_list(t_list *cmd_list);
void	print_cmd(t_cmd *cmd);

/*
** ------------------------------- Filler ------------------------------
*/

int		fill_argv(t_cmd *cmd);
int		fill_cmdlist_path(t_list *cmd_list, t_list *env);
int		fill_cmd_path(t_cmd *cmd, t_list *env);
char	**ft_list_to_tab_argv(t_list *argv);
// int		filler(t_list *pipe_list, t_list *env);
// int		contains_redir(char *buf);
// int		fill_redir(t_cmd *cmd);


#endif
