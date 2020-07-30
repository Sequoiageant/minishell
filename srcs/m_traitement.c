/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_traitement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:45 by grim              #+#    #+#             */
/*   Updated: 2020/07/30 18:14:23 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"


int		ft_traitement_cmdlist(t_list *cmd_list, t_list **env)
{
	t_cmd	*cmd;
	int		index;
	
	if (contains_pipe(cmd_list))
		ft_executable_cmd(cmd_list, *env);
	else
	{
		cmd = (t_cmd*)cmd_list->content;
		if (cmd->argc == 0) // pour eviter les "still reachable" si on lance un fork()
			return (SUCCESS);
		if (ft_check_built_in(cmd->argv[0], &index) == TRUE)
			ft_built_in(cmd, index, env);
		else if (ft_strcmp(cmd->argv[0], "exit") == 0)
			return (EXIT_CODE);
		else
			ft_executable_cmd(cmd_list, *env);
	}
	return (SUCCESS);
}

int		ft_traitement(t_list *pipe_list, t_list **env)
{
	t_list *cmd_list;
	// t_cmd	*cmd;
	
	while (pipe_list)
	{
		cmd_list = (t_list*)pipe_list->content;
		// ft_substitution(cmd_list, *env);
		#ifdef DEBUG_PARSING
			printf("\n--PARSING CMD\n");
		#endif
		parsing_cmd(cmd_list);
		#ifdef DEBUG_PARSING
			printf("\n--SUBST DONE--\n");
			print_commands(pipe_list);
		#endif
		(void)env;
		// cmd = (t_cmd*)cmd_list->content;
		// if (ft_traitement_cmdlist(cmd_list, env) == EXIT_CODE)
		// 	ms_exit(pipe_list, cmd->argc, cmd->argv, env);
		pipe_list = pipe_list->next;
	}
	return (SUCCESS);
}