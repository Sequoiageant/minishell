/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:13 by grim              #+#    #+#             */
/*   Updated: 2020/07/07 16:05:01 by grim             ###   ########.fr       */
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
#include "parsing.h"

#define TRUE 1
#define FALSE 0
#define PIPE_WRITE 1
#define PIPE_READ 0
#define BUF_SIZE 1000

extern	pid_t	new_pid;

typedef int (*t_built)(int argc, char *argv[], t_list **env);

typedef struct	s_key_val
{
	char			*key;
	char			*val;
}				t_key_val;

int			ms_echo(int argc, char *argv[], t_list **env);
int			ms_cd(int argc, char *argv[], t_list **env);
int			ms_pwd(int argc, char *argv[], t_list **env);
int			ms_export(int argc, char *argv[], t_list **env);
int			ms_env(int argc, char *argv[], t_list **env);
int			ms_unset(int argc, char *argv[], t_list **env);
int			ms_exit(int argc, char *argv[], t_list **env);
int			ft_fork(char **cmd, t_list **env);
int			ft_built_in(char **cmd, int argc, int index, t_list **env);
int			ft_traitement(t_list *cmd, t_list **env);
int			ft_init(t_list **env);
void		ft_print_env(t_list *env);
void		print_cmd(char **cmd);
t_key_val	*find_key_val(t_list *env, char *key);
void		print_env_elem(t_list *env, char *key);
void		del_key_val(void *elem);
void		del_pipe(void *elem);
int			ft_piped_cmd(t_list *pipe_list, t_list **env);
int			contains_pipe(t_list *cmd_list);
int			ft_check_built_in(char *cmd, int *index);
int			ft_fork_pipe(char **cmd1, char **cmd2, t_list **env); // test avec un pipe de seulement deux commandes
char		*ft_is_in_path(t_list *env, char *cmd);
char		**ft_list_to_tab(t_list *env);
void		free_tab2(char **tab);

#endif
