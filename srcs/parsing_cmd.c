/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 13:06:01 by grim             ###   ########.fr       */
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
		#ifdef DEBUG_PARSING
			printf("\nPARSING SUBST\n");
		#endif
		if (parse_cmd_subst(cmd, env) == FAILURE)
			return (FAILURE);
		// #ifdef DEBUG_PARSING
		// 	printf("\nPrinting cmd\n");
		// 	print_cmd(cmd);
		// #endif
		#ifdef DEBUG_PARSING
			printf("\nPARSING SPLIT\n");
		#endif
		if (parse_cmd_split(cmd) == FAILURE)
			return (FAILURE);
		// #ifdef DEBUG_PARSING
		// 	printf("\nPrinting cmd\n");
		// 	print_cmd(cmd);
		// #endif
		fill_cmd(cmd, env);
		#ifdef DEBUG_PARSING
			if(cmd_list->next)
				printf("\nNEXT CMD\n");
		#endif
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
