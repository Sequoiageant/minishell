/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 10:18:11 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int	split_buf(char *buf, t_list *env, t_list **pipe_list)
{
	ft_lstadd_back(pipe_list, ft_lstnew(NULL));
	add_cmd(*pipe_list);
	if (parser_split_buf(buf, env, pipe_list) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	parsing_cmd(t_list *cmd_list)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		if (parser_split_cmd(cmd) == FAILURE)
			return (FAILURE);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

static int	split_cmd(t_list *pipe_list)
{
	t_list *cmd_list;

	while (pipe_list)
	{
		cmd_list = (t_list *)pipe_list->content;
		if (parsing_cmd(cmd_list) == FAILURE)
			return (FAILURE);
		pipe_list = pipe_list->next;
	}
	return (SUCCESS);
}

static int	parser_split(char *buf, t_list *env, t_list **pipe_list)
{
	if (split_buf(buf, env, pipe_list) == FAILURE)
		return (FAILURE);
	if (split_cmd(*pipe_list) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int			ft_parse(char *buf, t_list *env, t_list **pipe_list)
{
	if (lexer(buf) == FAILURE)
	{
		g_glob.ret = 2;
		ft_putstr_fd("synthax error\n", 2);
		return (FAILURE);
	}
	if (parser_split(buf, env, pipe_list) == FAILURE)
		return (FAILURE);
	return (EXIT_SUCCESS);
}
