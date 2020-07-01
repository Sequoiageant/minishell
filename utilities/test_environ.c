/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:49:38 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/01 19:26:19 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

extern char **environ;

void	free_split(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	display_path(char **paths)
{
	size_t i;

	i = 0;
	while (paths[i])
	{
		ft_putendl_fd(paths[i], 1);
		i++;
	}
}

int		main(void)
{
	size_t	i;
	char	**line;
	char	**paths;

	i = 0;
	while (environ[i])
	{
		line = ft_split(environ[i], '=');
		if (ft_strcmp(line[0], "PATH") == 0)
		{
			// ft_putstr_fd(line[1], 1);
			paths = ft_split(line[1], ':');
			display_path(paths);
			free_split(paths);
			free_split(line);
			break;
		}
		free_split(line);
		i++;
	}
	return (0);
}