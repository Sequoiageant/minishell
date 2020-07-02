/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_traitement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:45 by grim              #+#    #+#             */
/*   Updated: 2020/07/02 19:03:52 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_simple_cmd(t_cmd *cmd, t_list **env)
{
	int	built_index;

	if (cmd->argc == 0) // cas ou la commande rentrée est vide ou n'est qu'une suite de ' ' --> a traiter à part car dans ce cas ft_split n'alloue aucune chaine de caractère
		return (0);
	if (ft_check_built_in(cmd->argv[0], &built_index) == TRUE)
	{
		ft_putstr_fd(">>built-in\n", 1);
		ft_built_in(cmd->argv, cmd->argc, built_index, env);
		// lance la fonction "cmd";
	}
	else
	{
		ft_putstr_fd(">>fork\n", 1);
		ft_fork(cmd->argv, env);
	}
	return (SUCCESS);
}

int		ft_traitement_cmdlist(t_list *cmd_list, t_list **env)
{
	t_cmd *cmd;
	
	if (contains_pipe(cmd_list))
		ft_piped_cmd(cmd_list, env);
	else
	{
		cmd = (t_cmd*)cmd_list->content;
		ft_simple_cmd(cmd, env);
	}
	return (SUCCESS);
}

int		ft_traitement(t_list *pipe_list, t_list **env)
{
	t_list *cmd_list;
	
	while (pipe_list)
	{
		cmd_list = (t_list*)pipe_list->content;
		ft_traitement_cmdlist(cmd_list, env);
		pipe_list = pipe_list->next;
	}
	return (SUCCESS);
}