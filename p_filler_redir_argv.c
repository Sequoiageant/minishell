/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_filler_redir_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:04:46 by grim              #+#    #+#             */
/*   Updated: 2020/07/02 18:13:06 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	contains_redir(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '>' || buf[i] == '<')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	fill_redir(t_cmd *cmd)
{
	int		i;
	char	*buf;

	buf = cmd->buf;
	i = 0;
	while (buf[i] != '>' && buf[i] != '<')
		i++;
	if (buf[i] == '>' && buf[i + 1] == '>')
	{
		cmd->output_file_append = 1;
		cmd->file = ft_substr(cmd->buf, i + 2, ft_strlen(cmd->buf) - i - 1);
	}
	else
	{
		if (buf[i] == '>')
			cmd->output_file = 1;
		else
			cmd->output_file = 1;
		cmd->file = ft_substr(cmd->buf, i + 1, ft_strlen(cmd->buf) - i);
	}
	cmd->buf = ft_substr(buf, 0, i);
	free(buf);
	return (1);
}

int	fill_argv(t_cmd *cmd)
{
	int i;

	cmd->argv = ft_split(cmd->buf, ' ');
	if (cmd->argv == NULL)
		return (FAILURE);
	i = 0;
	while (cmd->argv[i])
		i++;
	cmd->argc = i;
	return (SUCCESS);
}
