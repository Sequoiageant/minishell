/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_del.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:35:55 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 11:09:58 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	free_tab2(char **tab)
{
	size_t i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_tab2_int(int **tab, size_t num)
{
	size_t i;

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

void	del_env_node(t_list **env)
{
	del_key_val((*env)->content);
	free(*env);
	*env = NULL;
}

void	del_argv_node(t_list **argv)
{
	free(*argv);
	*argv = NULL;
}
