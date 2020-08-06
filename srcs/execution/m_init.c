/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:11 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 11:03:27 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int	is_in_str(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char		**ft_split_env(char *key_val)
{
	char	**elem;
	size_t	i;

	elem = NULL;
	elem = malloc(3 * sizeof(char *));
	if (elem)
	{
		i = 0;
		while (key_val[i] && key_val[i] != '=')
			i++;
		elem[0] = ft_substr(key_val, 0, i);
		if (is_in_str(key_val, '='))
			elem[1] = ft_substr(key_val, i + 1, ft_strlen(key_val));
		else
			elem[1] = NULL;
		elem[2] = NULL;
	}
	return (elem);
}

void		add_keyval_to_env(char *key, char *val, t_list **env)
{
	t_key_val *key_val;

	key_val = NULL;
	key_val = malloc(sizeof(t_key_val));
	if (key_val)
	{
		key_val->key = key;
		key_val->val = val;
		ft_lstadd_back(env, ft_lstnew(key_val));
	}
}

int			ft_init(t_list **env)
{
	char		**elem;
	size_t		i;

	ft_putstr_fd("Welcome to Minishell\n", 1);
	*env = NULL;
	i = 0;
	if (__environ[0])
	{
		while (__environ[i])
		{
			elem = ft_split_env(__environ[i]);
			if (elem)
			{
				add_keyval_to_env(elem[0], elem[1], env);
				free(elem);
			}
			else
				return (FAILURE);
			i++;
		}
	}
	return (SUCCESS);
}
