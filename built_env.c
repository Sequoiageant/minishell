/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/10 19:43:23 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	ms_env(int argc, char *argv[], t_list **env)
{
	(void)argc;
	(void)argv;
	ft_print_env(*env, FALSE);
	return (SUCCESS);
}

int	ms_export(int argc, char *argv[], t_list **env)
{
	(void)argc;
	t_key_val	*key_val;
	char		**tab;
	// t_key_val	*elem;
	size_t		i;

	if (argv[1])
	{
		i = 1;
		while(argv[i])
		{
			tab = ft_split_env(argv[i]);
			if (is_key_in_env(*env, tab[0]))
				change_env_val(*env, tab);
			else
			{
				key_val = malloc(sizeof(t_key_val));
				key_val->key = tab[0];
				key_val->val = tab[1];
				ft_lstadd_back(env, ft_lstnew(key_val));
			}
			free(tab);
			i++;
		}
	}
	else
		ft_print_env(*env, TRUE);
	return (SUCCESS);
}

int	ms_unset(int argc, char *argv[], t_list **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	size_t	i;

	if (argv[1])
	{
		i = 1;
		while (argv[i])
		{
			if (lst_delone_env(*env, argv[i]) == SUCCESS)
				printf("%s unset\n", argv[i]);
			i++;
		}
	}
	else
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
