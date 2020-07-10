/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/10 12:00:41 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	ms_env(int argc, char *argv[], t_list **env)
{
	(void)argc;
	(void)argv;
	char	**tab_env;

	tab_env = ft_list_to_tab(*env);
	if (tab_env)
	{
		display_tab2(tab_env);
		free(tab_env);
	}
	else
	{
		ft_putendl_fd("Environment variables are not accessible", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ms_export(int argc, char *argv[], t_list **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	return (0);
}

int	ms_unset(int argc, char *argv[], t_list **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	return (0);
}
