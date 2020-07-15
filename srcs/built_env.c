/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/13 16:51:38 by julnolle         ###   ########.fr       */
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
/*
t_list	*sort_list_by_key(t_list *env)
{
	t_list		*sorted_env;
	t_key_val	*new;
	char		**env_tab;
	char		**elem;
	size_t		i;

	env_tab = ft_list_to_tab(env);
	ft_n_sort_string_tab(env_tab, '=');
	i = 0;
	sorted_env = NULL;
	while(env_tab[i])
	{
		elem = ft_split_env(env_tab[i]);
		new = malloc(sizeof(t_key_val));
		new->key = elem[0];
		new->val = elem[1];
		ft_lstadd_back(&sorted_env, ft_lstnew(new));
		free(elem);
		i++;
	}
	free_tab2(env_tab);
	return (sorted_env);
}
*/
void	print_sorted_list(t_list *env)
{
	char		**env_tab;

	env_tab = ft_list_to_tab(env);
	ft_n_sort_string_tab(env_tab, '=');
	display_tab2_export(env_tab);
	free_tab2(env_tab);
}

int	ms_export(int argc, char *argv[], t_list **env)
{
	t_key_val	*key_val;
	// t_list		*sorted_env;
	char		**tab;
	size_t		i;

	if (argc > 1)
	{
		i = 1;
		while(argv[i])
		{
			tab = ft_split_env(argv[i]);
			if (is_key_in_env(*env, tab[0]))
				change_env_val(*env, tab);
			else if (tab[1])
			{
				printf("tab1:%s\n", tab[1]);
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
	{
		print_sorted_list(*env);
		// sorted_env = sort_list_by_key(*env);
		// ft_print_env(sorted_env, TRUE);
		// ft_lstclear(&sorted_env, &del_key_val);
	}
	return (SUCCESS);
}

int	ms_unset(int argc, char *argv[], t_list **env)
{
	size_t	i;

	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			lst_delone_env(*env, argv[i]);
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
