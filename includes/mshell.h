/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:13 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/11 14:51:05 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H
# define MSHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "parsing.h"

# define PIPE_WRITE		1
# define PIPE_READ		0
# define CTRLC_RET		130
# define CTRLBACK_RET	131
# define NB_BLT			6
# define EXIT_CODE		2

/*
** ---------------------- Typedef and structures ---------------------
*/

typedef int	(*t_built)(int argc, char *argv[], t_list **env);

typedef struct	s_key_val
{
	char	*key;
	char	*val;
}				t_key_val;

typedef struct	s_globale
{
	pid_t	pid;
	int		ret;
}				t_globale;

extern	t_globale	g_glob;
/*
** ----------------------------- Built-in -----------------------------
*/

int				ft_built_in(t_cmd *cmd, int index, t_list **env);
int				ms_echo(int argc, char *argv[], t_list **env);
int				ms_cd(int argc, char *argv[], t_list **env);
int				cd_home_not_set(t_key_val *key);
int				cd_too_many_args();
int				cd_back_to_oldpwd(t_list *env);
char			*cd_find_path(t_list *env, char *cmd);
int				ms_pwd(int argc, char *argv[], t_list **env);
int				ms_export(int argc, char *argv[], t_list **env);
int				ms_env(int argc, char *argv[], t_list **env);
int				ms_unset(int argc, char *argv[], t_list **env);
void			ms_exit(t_list *pipe_list, int ac, char **argv, t_list **env);
int				ft_check_built_in(char *cmd, int *index);
int				is_valid_identifier(char *str);

/*
** ----------------------------- Executes -----------------------------
*/

int				ft_init(t_list **env);
int				ft_simple_cmd_fork(char **cmd, t_list **env, char *cmd_path);
int				ft_traitement(t_list *pipe_list, t_list **env);
int				ft_executable_cmd(t_list *cmd_list, t_list *env);
int				ft_executable_cmd_single(t_list *cmd_list, t_list *env);
size_t			ft_build_pipes(t_list *cmd_list, int ***fd);
int				dup_close_pipes(int *fd[2], int fd_in, int fd_out, int num);
void			close_wait_free(int *fd[2], size_t num_pipe, char **env_tab);
void			close_pipes(int *fd[2], int num);
void			ft_wait(int num_pipe);
int				ft_redirs(t_cmd *cmd);
void			ft_exec_solo_cmd(t_list *cmd_elem, char **env_tab);
void			ft_handle_pipes(t_list *cmd_list, t_list **env, char **env_tab);

/*
** ----------------------------- Expansion ---------------------------
*/

int				ft_expansion(t_list *cmd_list, t_list *env);
int				ft_handle_argv(char **t, t_list *e, t_list **f, int *r);
int				is_even(int nb);
void			ft_tab_to_list(t_list **list, char **tab);
size_t			tab2_size(char **tab);
size_t			ft_strclen(const char *s, int c);
void			ft_realloc(char **new, char **src);
void			ft_realloc_or_free(char **final, char **src);

/*
** ------------------------------- Utils ------------------------------
*/

void			del_key_val(void *elem);
void			del_env_node(t_list **env);
void			del_argv_node(t_list **argv);
void			del_cmd(void *elem);
void			del_pipe(void *elem);
void			del_argv_list_elem(void *elem);
void			free_tab2(char **tab);
void			free_tab2_int(int **tab, size_t num);
void			free_tab2_stop(char **tab, size_t stop);

t_key_val		*find_key_val(t_list *env, char *key);
char			*find_env_val(t_list *env, const char *key);
void			ft_print_env(t_list *env);
int				is_key_in_env(t_list *env, char *key);
void			change_env_val(t_list **env, char *key, char *val);
char			**ft_split_env(char *key_val);
char			**ft_list_to_tab(t_list *env);
void			put_err(char *cmd, char *arg, char *last, int minishell);
void			add_keyval_to_env(char *key, char *val, t_list **env);

void			print_env_elem(t_list *env, char *key);
void			ft_print_status(int status);
void			display_tab2(char **tab);
void			display_tab2_export(char **tab);

#endif
