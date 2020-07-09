/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:11 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 17:00:39 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

char	**ft_split_env(char *key_val)
{
	char	**elem;
	int		i;

	elem = malloc(2 * sizeof(char *));
	i = 0;
	while (key_val[i] && key_val[i] != '=')
		i++;
	elem[0] = ft_substr(key_val, 0, i);
	elem[1] = ft_substr(key_val, i + 1, ft_strlen(key_val));
	return (elem);
}

int		ft_init(t_list **env)
{
	char		**elem;
	t_key_val	*key_val;
	int			i;

	ft_putstr_fd("Welcome to Minishell\n", 1);
	*env = NULL;
	i = 0;
	while(__environ[i])
	{
		// printf("%s\n", __environ[i]);
		elem = ft_split_env(__environ[i]);
		key_val = malloc(sizeof(t_key_val));
		key_val->key = elem[0];
		key_val->val = elem[1];
		ft_lstadd_back(env, ft_lstnew(key_val));
		free(elem);
		i++;
	}
	return (0);
}