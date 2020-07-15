/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:31:47 by grim              #+#    #+#             */
/*   Updated: 2020/07/10 13:48:55 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	ft_redir_output(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_redir_output_append(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_redir_input(char *file)
{
	int fd;

	fd = open(file, O_RDWR);
	if (fd == -1)
	{
		perror(file);
		exit(0);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	ft_redirs(t_cmd *cmd)
{
	if (cmd->output_file)
		ft_redir_output(cmd->file);
	if (cmd->output_file_append)
		ft_redir_output_append(cmd->file);
	if (cmd->input_file)
		ft_redir_input(cmd->file);
}