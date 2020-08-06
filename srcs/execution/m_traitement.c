/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_traitement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:45 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 10:40:27 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int	contains_pipe(t_list *cmd_list)
{
	if (cmd_list->next)
		return (TRUE);
	else
		return (FALSE);
}

static int	ft_traitement_cmdlist(t_list *cmd_list, t_list **env)
{
	t_cmd	*cmd;
	int		index;

	if (contains_pipe(cmd_list))
		ft_executable_cmd(cmd_list, *env);
	else
	{
		cmd = (t_cmd*)cmd_list->content;
		if (ft_check_built_in(cmd->argv[0], &index) == TRUE)
			ft_built_in(cmd, index, env);
		else if (ft_strcmp(cmd->argv[0], "exit") == 0)
			return (EXIT_CODE);
		else
			ft_executable_cmd_single(cmd_list, *env);
	}
	return (SUCCESS);
}

int			ft_traitement(t_list *pipe_list, t_list **env)
{
	t_list	*cmd_list;
	t_cmd	*cmd;

	while (pipe_list)
	{
		cmd_list = (t_list*)pipe_list->content;
		ft_expansion(cmd_list, *env);
		clean_quotes(cmd_list);
		fill_cmdlist_path(cmd_list, *env);
		cmd = (t_cmd*)cmd_list->content;
		if (ft_traitement_cmdlist(cmd_list, env) == EXIT_CODE)
			ms_exit(pipe_list, cmd->argc, cmd->argv, env);
		pipe_list = pipe_list->next;
	}
	return (SUCCESS);
}
