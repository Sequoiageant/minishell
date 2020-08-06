/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:39 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 13:05:35 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

char		**ft_list_to_tab(t_list *env)
{
	char		**tab;
	t_key_val	*e;
	size_t		size;
	size_t		i;

	size = ft_lstsize(env);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (tab)
	{
		tab[size] = NULL;
		i = 0;
		while (env)
		{
			e = (t_key_val *)(env->content);
			tab[i] = ft_calloc(ft_strlen(e->key) + ft_strlen(e->val) + 2, 1);
			ft_strcat(tab[i], e->key);
			ft_strcat(tab[i], "=");
			ft_strcat(tab[i], e->val);
			env = env->next;
			i++;
		}
	}
	return (tab);
}

int			is_key_in_env(t_list *env, char *key)
{
	t_key_val *elem;

	while (env)
	{
		elem = (t_key_val *)env->content;
		if (ft_strcmp(elem->key, key) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

char		*find_env_val(t_list *env, const char *key)
{
	t_key_val *elem;

	while (env)
	{
		elem = (t_key_val *)env->content;
		if (ft_strcmp(elem->key, key) == 0)
			return (elem->val);
		env = env->next;
	}
	return (NULL);
}

t_key_val	*find_key_val(t_list *env, char *key)
{
	t_key_val *elem;

	while (env)
	{
		elem = (t_key_val *)env->content;
		if (ft_strcmp(elem->key, key) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

void		change_env_val(t_list **env, char *key, char *val)
{
	t_key_val	*elem;
	t_list		*tmp;

	tmp = *env;
	if (tmp)
	{
		while (tmp)
		{
			elem = (t_key_val *)tmp->content;
			if (ft_strcmp(elem->key, key) == 0)
			{
				free(elem->val);
				elem->val = NULL;
				elem->val = val;
				return ;
			}
			tmp = tmp->next;
		}
	}
	else
		add_keyval_to_env(ft_strdup(key), val, env);
}
