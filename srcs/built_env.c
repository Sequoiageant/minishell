/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/18 12:08:50 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	ms_env(int argc, char *argv[], t_list **env)
{
	(void)argc;
	(void)argv;
	ft_print_env(*env);
	return (SUCCESS);
}

void	print_sorted_list(t_list *env)
{
	char		**env_tab;

	env_tab = ft_list_to_tab(env);
	ft_n_sort_string_tab(env_tab, '=');
	display_tab2_export(env_tab);
	free_tab2(env_tab);
}

int	is_valid_identifier(char *str)
{
	if ((!ft_isalpha(str[0]) && str[0] != '_') || !ft_isalnum_str(str))
		return (FALSE);
	return (TRUE);
}

int	ms_export(int argc, char *argv[], t_list **env)
{
	char		**tab;
	size_t		i;

	if (argc > 1)
	{
		i = 1;
		while(argv[i])
		{
			tab = ft_split_env(argv[i]);
			if (tab)
			{
				if (is_key_in_env(*env, tab[0]))
					change_env_val(*env, tab);
				else if (tab[1] && is_valid_identifier(tab[0]))
					add_keyval_to_env(tab, env);
				else if (!is_valid_identifier(tab[0]))
						put_err("export: `", argv[i], "': not a valid identifier", TRUE);
				free(tab);
			}
			i++;
		}
	}
	else
		print_sorted_list(*env);
	return (SUCCESS);
}

int	ms_unset(int argc, char *argv[], t_list **env)
{
	size_t	i;

	if (argc > 1)
	{
		{
			i = 1;
			while (argv[i])
			{
				if (is_valid_identifier(argv[i]))
					lst_delone_env(*env, argv[i]);
				else
				{
					put_err("export: `", argv[i], "': not a valid identifier", TRUE);
					return	(FAILURE);
				}
				i++;
			}
		}
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
