/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:31:47 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 10:40:49 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int	ft_redir_out(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		put_err(file, ": ", strerror(errno), TRUE);
		g_glob.ret = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	ft_redir_append(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		put_err(file, ": ", strerror(errno), TRUE);
		g_glob.ret = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	ft_redir_in(char *file)
{
	int fd;

	fd = open(file, O_RDWR);
	if (fd == -1)
	{
		put_err(file, ": ", strerror(errno), TRUE);
		g_glob.ret = 1;
		return (FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (SUCCESS);
}

static int	ft_handle_redir(t_redir *redir)
{
	if (redir->state == -1 || redir->file == NULL)
	{
		put_err(redir->original, ": ", "ambiguous redir", TRUE);
		g_glob.ret = 1;
		return (FAILURE);
	}
	if (redir->state == REDIR_OUT)
		if (ft_redir_out(redir->file) == FAILURE)
			return (FAILURE);
	if (redir->state == REDIR_APPEND)
		if (ft_redir_append(redir->file) == FAILURE)
			return (FAILURE);
	if (redir->state == REDIR_IN)
		if (ft_redir_in(redir->file) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int			ft_redirs(t_cmd *cmd)
{
	t_list	*redir_list;

	redir_list = cmd->redir;
	while (redir_list)
	{
		if (ft_handle_redir((t_redir*)redir_list->content) == FAILURE)
			return (FAILURE);
		redir_list = redir_list->next;
	}
	return (SUCCESS);
}
