/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_executable_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:15:15 by grim              #+#    #+#             */
/*   Updated: 2020/08/04 11:44:04 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	contains_pipe(t_list *cmd_list)
{
	if (cmd_list->next)
		return (TRUE);
	else
		return (FALSE);
}

int	ft_build_pipes(t_list *cmd_list, int ***fd)
{
	int num_cmd;
	int i;

	num_cmd = 0;
	while (cmd_list)
	{
		num_cmd++;
		cmd_list = cmd_list->next;
	}
	if (num_cmd == 1)
		return(0);
	*fd = malloc((num_cmd - 1) * sizeof(**fd));
	i = 0;
	while (i < num_cmd - 1)
	{
		(*fd)[i] = malloc(2 * sizeof(int));
		pipe((*fd)[i]);
		i++;
	}
	return (i);
}

void	close_pipes(int *fd[2], int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	dup_close_pipes(int *fd[2], int fd_in, int fd_out, int num)
{
	if (fd_out)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (fd_in)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	close_pipes(fd, num);
}

void	ft_wait(int num_pipe)
{
	int i;
	int status;
	
	i = 0;
	while (i < num_pipe + 1)
	{
		if (wait(&status) == g_glob.pid) // si c'est la dernière commande (pid = g_glob.pid), on set g_glob.ret à son exit status
			if (WIFEXITED(status))
				g_glob.ret = WEXITSTATUS(status);
		i++;
	}
}
