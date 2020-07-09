/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_filler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 10:09:13 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 11:20:05 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	fill_cmd(t_cmd *cmd, t_list *env)
{
	char *file;

	if (contains_redir(cmd->buf))
	{
		fill_redir(cmd);
		file = cmd->file;
		cmd->file = ft_strtrim(file, " ");
		free(file);
	}
	if (fill_argv(cmd) == FAILURE)
		return (FAILURE);
	if (fill_cmd_path(cmd, env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	fill_pipe(t_list *pipe_list, t_list *env)
{
	t_list	*cmd_list;
	t_cmd	*cmd;

	cmd_list = (t_list*)pipe_list->content;
	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		if (fill_cmd(cmd, env) == FAILURE)
			return (FAILURE);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

int	filler(t_list *pipe_list, t_list *env)
{
	while (pipe_list)
	{
		if (fill_pipe(pipe_list, env) == FAILURE)
			return (FAILURE);
		pipe_list = pipe_list->next;
	}
	return (SUCCESS);
}
