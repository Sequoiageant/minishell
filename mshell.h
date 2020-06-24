/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:13 by grim              #+#    #+#             */
/*   Updated: 2020/06/24 15:52:06 by grim             ###   ########.fr       */
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
#include <errno.h>
#include "parsing.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1
#define BUF_SIZE 1000

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
int			ft_fork(char **cmd);
int			ft_built_in(char **cmd, int argc, int index, t_list **env);
// int			ft_traitement(char **cmd, t_list **env);
int			ft_traitement(t_list *cmd, t_list **env);
int			ft_init(t_list **env);
void		ft_print_env(t_list *env);
void		print_cmd(char **cmd);
t_key_val	*find_key_val(t_list *env, char *key);
void		print_env_elem(t_list *env, char *key);
void		del_cmd(void *elem);
void		del_key_val(void *elem);

#endif
