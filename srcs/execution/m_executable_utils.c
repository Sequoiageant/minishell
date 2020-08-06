/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_executable_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:15:15 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 11:11:26 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

size_t	ft_build_pipes(t_list *cmd_list, int ***fd)
{
	size_t	num_cmd;
	size_t	i;

	num_cmd = 0;
	while (cmd_list)
	{
		num_cmd++;
		cmd_list = cmd_list->next;
	}
	if (num_cmd == 1)
		return (0);
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

int		dup_close_pipes(int *fd[2], int fd_in, int fd_out, int num)
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
	return (TRUE);
}

void	close_wait_free(int *fd[2], size_t num_pipe, char **env_tab)
{
	close_pipes(fd, num_pipe);
	ft_wait(num_pipe);
	g_glob.pid = 0;
	free_tab2_int(fd, num_pipe);
	free_tab2(env_tab);
}

void	ft_wait(int num_pipe)
{
	int i;
	int status;

	i = 0;
	while (i < num_pipe + 1)
	{
		if (wait(&status) == g_glob.pid)
			if (WIFEXITED(status))
				g_glob.ret = WEXITSTATUS(status);
		i++;
	}
}
