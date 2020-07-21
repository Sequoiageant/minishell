/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/21 12:11:01 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

static void	print_sorted_list(t_list *env)
{
	char	**env_tab;

	env_tab = ft_list_to_tab(env);
	ft_n_sort_string_tab(env_tab, '=');
	display_tab2_export(env_tab);
	free_tab2(env_tab);
}

static	int	handle_env(t_list **env, char **tab, char *arg)
{
	if (is_key_in_env(*env, tab[0]))
		change_env_val(*env, tab[0], tab[1]);
	else if (tab[1] && is_valid_identifier(tab[0]))
		add_keyval_to_env(tab, env);
	else if (!is_valid_identifier(tab[0]))
	{
		put_err("export: `", arg, "': not a valid identifier", TRUE);
		return (FAILURE);
	}
	return (SUCCESS);
}

int			ms_export(int argc, char *argv[], t_list **env)
{
	char	**tab;
	size_t	i;
	int		ret;

	ret = SUCCESS;
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			tab = ft_split_env(argv[i]);
			if (tab)
			{
				ret = handle_env(env, tab, argv[i]);
				free(tab);
			}
			else
				ret = FAILURE;
			i++;
		}
	}
	else
		print_sorted_list(*env);
	return (ret);
}
