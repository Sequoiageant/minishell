/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:39 by grim              #+#    #+#             */
/*   Updated: 2020/06/23 18:15:48 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	ft_print_env(t_list *env)
{
	t_key_val	*elem;

	while (env)
	{
		elem = (t_key_val *)(env->content);
		printf("clé: %s\n", elem->key);
		printf("val: %s\n", elem->val);
		env = env->next;
	}
}

void	print_cmd(char **cmd)
{
	int i = 0;
	while (cmd[i])
	{
		// ft_putnbr_fd(i, 1);
		// ft_putstr_fd("\n", 1);
		ft_putstr_fd(cmd[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
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
	return(NULL);
}

void	print_env_elem(t_list *env, char *key)
{
	t_key_val *elem;
	
	elem = find_key_val(env, key);
	if (elem)
	{
		ft_putstr_fd(elem->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(elem->val, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("Unknown env variable\n", 1);
}