/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_traitement_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:45 by grim              #+#    #+#             */
/*   Updated: 2020/07/19 18:07:11 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_choose_builtin_or_bin(t_list *cmd_list, t_list **env, char **env_tab)
{
	t_cmd	*cmd;
	int		index;

	cmd = (t_cmd*)cmd_list->content;
	if (cmd->argc == 0)
		return (SUCCESS);
	if (ft_check_built_in(cmd->argv[0], &index) == TRUE)
	{
		// ft_putendl_fd("builtin", 2);
		ft_built_in(cmd, index, env);
	}
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (EXIT_CODE);
	else
	{
		// ft_putendl_fd("binary", 2);
		ft_exec_cmd(cmd_list, env_tab);
	}
	return (SUCCESS);
}

int		ft_traitement_cmdlist(t_list *cmd_list, t_list **env)
{
	t_cmd	*cmd;
	int		index;
	char	**env_tab;

	env_tab = ft_list_to_tab(*env);
	if (contains_pipe(cmd_list))
		ft_handle_pipes(cmd_list, env, env_tab);
	else
	{
		cmd = (t_cmd*)cmd_list->content;
		if (cmd->argc == 0)
		{
			free(env_tab);
			return (SUCCESS);
		}
		if (ft_check_built_in(cmd->argv[0], &index) == TRUE)
			ft_built_in(cmd, index, env);
		else if (ft_strcmp(cmd->argv[0], "exit") == 0)
			return (EXIT_CODE);
		else
			ft_exec_solo_cmd(cmd_list, env_tab);
	}
	free(env_tab);
	return (SUCCESS);
}

int		ft_traitement(t_list *pipe_list, t_list **env)
{
	t_list *cmd_list;
	t_cmd	*cmd;
	
	while (pipe_list)
	{
		cmd_list = (t_list*)pipe_list->content;
		cmd = (t_cmd*)cmd_list->content;
		if (ft_traitement_cmdlist(cmd_list, env) == EXIT_CODE)
			ms_exit(pipe_list, cmd->argc, cmd->argv, env);
		pipe_list = pipe_list->next;
	}
	return (SUCCESS);
}