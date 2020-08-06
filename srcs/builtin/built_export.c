/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/06 09:26:05 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static void	ft_n_sort_string_tab(char **tab, char stop)
{
	size_t	i;
	size_t	len;
	char	*temp;

	i = 0;
	while (tab[i + 1])
	{
		len = ft_strclen(tab[i], stop);
		if (ft_strncmp(tab[i], tab[i + 1], len) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

static void	print_sorted_list(t_list *env)
{
	char	**env_tab;
	char	**tab;
	size_t	i;

	env_tab = ft_list_to_tab(env);
	ft_n_sort_string_tab(env_tab, '=');
	i = 0;
	while (env_tab[i])
	{
		tab = ft_split_env(env_tab[i]);
		if (tab && (ft_strcmp(tab[0], "_") != 0))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tab[0], 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tab[1], 1);
			ft_putendl_fd("\"", 1);
			free_tab2(tab);
		}
		else if (tab && (ft_strcmp(tab[0], "_") == 0))
			free_tab2(tab);
		i++;
	}
	free_tab2(env_tab);
}

static	int	handle_env(t_list **env, char **tab, int ret)
{
	if (is_key_in_env(*env, tab[0]) && tab[1])
	{
		change_env_val(env, tab[0], tab[1]);
		free(tab[0]);
	}
	else if (tab[1] && is_valid_identifier(tab[0]))
		add_keyval_to_env(tab[0], tab[1], env);
	else if (!is_valid_identifier(tab[0]))
	{
		put_err("export: `", tab[0], "': not a valid identifier", TRUE);
		free(tab[0]);
		free(tab[1]);
		return (FAILURE);
	}
	else if (!tab[1])
	{
		free(tab[0]);
		free(tab[1]);
		return (FAILURE);
	}
	return (ret == FAILURE ? FAILURE : SUCCESS);
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
			if ((tab = ft_split_env(argv[i])))
			{
				ret = handle_env(env, tab, ret);
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
