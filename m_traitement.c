/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_traitement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:45 by grim              #+#    #+#             */
/*   Updated: 2020/06/25 13:47:50 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_check_built_in(char *cmd, int *index)
{
	char			*built[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int				i;
	int				res;

	// index: index du built_in correspondant à la commande, au sein du tableau "built"
	i = 0;
	while (built[i])
	{
		if ((res = ft_strcmp(cmd, built[i]) == 0))
		{
			*index = i;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int		ft_traitement(t_list *cmd_list, t_list **env)
{
	int	built_index;
	t_cmd *cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
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
			ft_fork(cmd->argv);
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}