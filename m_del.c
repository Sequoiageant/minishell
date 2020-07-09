/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_del.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:35:55 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 10:50:29 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	free_tab2(char **tab)
{
	int i;

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

void	del_key_val(void *elem)
{
	t_key_val *key_val;

	key_val = (t_key_val*)elem;
	free(key_val->key);
	free(key_val->val);
	free(key_val);
}

void    del_cmd(void *elem)
{
    t_cmd	*cmd;

    cmd = (t_cmd*)elem;
	if (cmd->file)
    	free(cmd->file);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	free(cmd->buf);
	free_tab2(cmd->argv);
	free(cmd);
}

void	del_pipe(void *elem)
{
	t_list *cmd_list;

	cmd_list = (t_list*)elem;
	ft_lstclear(&cmd_list, &del_cmd);
}
