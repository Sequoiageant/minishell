/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:39 by grim              #+#    #+#             */
/*   Updated: 2020/07/10 19:19:21 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	display_tab2(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
}

char		**ft_list_to_tab(t_list *env)
{
	char		**env_tab;
	t_key_val	*elem;
	int			size;
	int			i;

	size = ft_lstsize(env);
	env_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (env_tab)
	{
		env_tab[size] = NULL;
		i = 0;
		while (env)
		{
			elem = (t_key_val *)(env->content);
			env_tab[i] = ft_calloc(ft_strlen(elem->key) + ft_strlen(elem->val) + 2, 1);
			ft_strcat(env_tab[i], elem->key);
			ft_strcat(env_tab[i], "=");
			ft_strcat(env_tab[i], elem->val);
			env = env->next;
			i++;
		}
	}
	return (env_tab);
}

void	ft_print_env(t_list *env)
{
	t_key_val	*elem;

	while (env)
	{
		elem = (t_key_val *)(env->content);
		ft_putstr_fd(elem->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(elem->val, 1);
		env = env->next;
	}
}

int		is_key_in_env(t_list *env, char *key)
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

void	change_env_val(t_list *env, char **key_val)
{
	t_key_val *elem;

	while (env)
	{
		elem = (t_key_val *)env->content;
		if (ft_strcmp(elem->key, key_val[0]) == 0)
		{
			free(elem->val);
			elem->val = NULL;
			elem->val = key_val[1]; 
		}
		env = env->next;
	}
}

int		lst_delone_env(t_list *env, char *key)
{
	t_list		*tmp;
	t_key_val	*elem;

	tmp = env;
	while (env)
	{
		elem = (t_key_val *)env->content;
		if (ft_strcmp(elem->key, key) == 0)
		{
			tmp->next = env->next;
			free(elem->key);
			free(elem->val);
			free(elem);
			// env->next = tmp->next;
			return (SUCCESS); 
		}
		tmp = tmp->next;
		env = env->next;
	}
	return (FAILURE);
}

void	print_env_elem(t_list *env, char *key)
{
	t_key_val *elem;
	
	elem = find_key_val(env, key);
	if (elem)
	{
		ft_putstr_fd(elem->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(elem->val, 1);
	}
	else
		ft_putstr_fd("Unknown env variable\n", 1);
}