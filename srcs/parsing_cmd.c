/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 11:32:19 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"


int	fill_cmd(t_cmd *cmd, t_list *env)
{
	cmd->argv = ft_list_to_tab_argv(cmd->argv_list);
	cmd->argc = ft_lstsize(cmd->argv_list);
	if (cmd->argv[0]) // si NULL cause un segfault
	{	if (fill_cmd_path(cmd, env) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int			parsing_cmd(t_list *cmd_list, t_list *env)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		if (parse_cmd_subst(cmd, env) == FAILURE)
			return (FAILURE);
		// if (parse_cmd_split(cmd) == FAILURE)
		// 	return (FAILURE);
		// fill_cmd(cmd, env);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
