/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:31:47 by grim              #+#    #+#             */
/*   Updated: 2020/07/22 18:55:23 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

// static int	ft_redir_output(char *file)
// {
// 	int fd;

// 	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
// 	if (fd != -1)
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	else
// 	{
// 		put_err(file, ": ", strerror(errno), TRUE);
// 		g_glob.ret = 1;
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

// static int	ft_redir_output_append(char *file)
// {
// 	int fd;

// 	fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
// 	if (fd != -1)
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	else
// 	{
// 		put_err(file, ": ", strerror(errno), TRUE);
// 		g_glob.ret = 1;
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

// static int	ft_redir_input(char *file)
// {
// 	int fd;

// 	fd = open(file, O_RDWR);
// 	if (fd == -1)
// 	{
// 		put_err(file, ": ", strerror(errno), TRUE);
// 		g_glob.ret = 1;
// 		return (FAILURE);
// 	}
// 	else
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	return (SUCCESS);
// }

int			ft_redirs(t_cmd *cmd)
{
// 	int	ret;

// 	ret = SUCCESS;
// 	if (cmd->output_file)
// 		ret = ft_redir_output(cmd->file);
// 	if (cmd->output_file_append)
// 		ret = ft_redir_output_append(cmd->file);
// 	if (cmd->input_file)
// 		ret = ft_redir_input(cmd->file);
// 	return (ret);
	(void)cmd;
	return(SUCCESS);
}
