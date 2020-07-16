/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:13 by grim              #+#    #+#             */
/*   Updated: 2020/07/16 09:09:02 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H
# define MSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "parsing.h"

#define TRUE		1
#define FALSE		0
#define SUCCESS		0
#define FAILURE		-1
#define EXIT_CODE	2
#define PIPE_WRITE	1
#define PIPE_READ	0
// #define BUF_SIZE 1000
#define NB_BLT		6

extern	pid_t	g_new_pid;

typedef int (*t_built)(int argc, char *argv[], t_list **env);

typedef struct	s_key_val
{
	char			*key;
	char			*val;
}				t_key_val;

/*
** ----------------------------- Built-in -----------------------------
*/

int			ft_built_in(t_cmd *cmd, int index, t_list **env);
int			ms_echo(int argc, char *argv[], t_list **env);
int			ms_cd(int argc, char *argv[], t_list **env);
int			ms_pwd(int argc, char *argv[], t_list **env);
int			ms_export(int argc, char *argv[], t_list **env);
int			ms_env(int argc, char *argv[], t_list **env);
int			ms_unset(int argc, char *argv[], t_list **env);
void		ms_exit(t_list *pipe_list, int ac, char **argv, t_list **env);
int			ft_check_built_in(char *cmd, int *index);

/*
** ----------------------------- Executes -----------------------------
*/

int			ft_init(t_list **env);
int			ft_simple_cmd_fork(char **cmd, t_list **env, char *cmd_path);
int			ft_traitement(t_list *cmd, t_list **env);
int			ft_executable_cmd(t_list *pipe_list, t_list *env);
int			contains_pipe(t_list *cmd_list);
int			ft_build_pipes(t_list *cmd_list, int ***fd);
void		dup_close_pipes(int *fd[2], int fd_in, int fd_out, int num);
void		ft_redirs(t_cmd *cmd);

/*
** ------------------------------- Utils ------------------------------
*/

void		del_key_val(void *elem);
void   		del_cmd(void *elem);
void		del_pipe(void *elem);
char		*find_in_env_path(t_list *env, char *cmd);
t_key_val	*find_key_val(t_list *env, char *key);
void		ft_print_env(t_list *env, int declare);
void		print_env_elem(t_list *env, char *key);
void		print_cmd(char **cmd);
void		ft_print_status(int status);
void		display_tab2(char **tab);
void		display_tab2_export(char **tab);
void		free_tab2(char **tab);
void		free_tab2_int(int **tab, int num);
void		ft_n_sort_string_tab(char **tab, char stop);
int			is_key_in_env(t_list *env, char *key);
int			lst_delone_env(t_list *env, char *key);
void		change_env_val(t_list *env, char **key_val);
char		**ft_split_env(char *key_val);
char		**ft_list_to_tab(t_list *env);
void		put_err(char *cmd, char *arg, char *last);
void		add_keyval_to_env(char **elem, t_list **env);

#endif

