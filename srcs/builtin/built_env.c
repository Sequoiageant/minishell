/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/05 20:38:59 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int			is_valid_identifier(char *str)
{
	if ((!ft_isalpha(str[0]) && str[0] != '_') || !ft_isalnum_str(str))
		return (FALSE);
	return (TRUE);
}

int			ms_env(int argc, char **av, t_list **env)
{
	t_key_val	*elem;

	(void)argc;
	(void)av;
	while (*env)
	{
		elem = (t_key_val *)((*env)->content);
		ft_putstr_fd(elem->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(elem->val, 1);
		(*env) = (*env)->next;
	}
	return (SUCCESS);
}

static void	lst_delone_env(t_list **env, char *key)
{
	t_list		*tmp;
	t_list		*before;
	t_key_val	*elem;
	int			i;

	before = *env;
	tmp = *env;
	i = 0;
	while (tmp)
	{
		elem = (t_key_val *)tmp->content;
		if (ft_strcmp(elem->key, key) == 0)
		{
			if (i != 0)
				before->next = tmp->next;
			else
			{
				before = tmp->next;
				*env = before;
			}
			del_env_node(&tmp);
			return ;
		}
		before = tmp;
		i++;
		tmp = tmp->next;
	}
}

int			ms_unset(int argc, char **av, t_list **env)
{
	size_t	i;
	int		ret;

	ret = SUCCESS;
	if (argc > 1)
	{
		{
			i = 1;
			while (av[i])
			{
				if (is_valid_identifier(av[i]))
					lst_delone_env(env, av[i]);
				else
				{
					put_err("unset: `", av[i], "': not a valid identifier", 1);
					ret = FAILURE;
				}
				i++;
			}
		}
	}
	return (ret);
}
