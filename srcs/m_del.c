/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_del.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:35:55 by grim              #+#    #+#             */
/*   Updated: 2020/07/13 17:12:03 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	free_tab2(char **tab)
{
	int i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_tab2_int(int **tab, int num)
{
	int i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < num)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	del_key_val(void *elem)
{
	t_key_val *key_val;

	key_val = (t_key_val*)elem;
	free(key_val->key);
	key_val->key = NULL;
	free(key_val->val);
	key_val->val = NULL;
	free(key_val);
	key_val = NULL;
}

void    del_cmd(void *elem)
{
    t_cmd	*cmd;

    cmd = (t_cmd*)elem;
	if (cmd->file)
	{
    	free(cmd->file);
    	cmd->file = NULL;
	}
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
    	cmd->cmd_path = NULL;
	}
	free(cmd->buf);
   	cmd->buf = NULL;
	free_tab2(cmd->argv);
	free(cmd);
	cmd = NULL;
}

void	del_pipe(void *elem)
{
	t_list *cmd_list;

	cmd_list = (t_list*)elem;
	ft_lstclear(&cmd_list, &del_cmd);
}
