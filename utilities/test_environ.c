/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:49:38 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/02 14:44:48 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Compilation line :
// gcc -Wall -Wextra -Werror test_environ.c -L../libft/ -lft -I../libft/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"

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

void	display_path(char **path)
{
	size_t i;

	i = 0;
	while (path[i])
	{
		ft_putendl_fd(path[i], 1);
		i++;
	}
}

int		ft_ckeck_bin(DIR *dir, char *cmd)
{
	struct dirent	*dir_content;
	(void)cmd;

	while ((dir_content = readdir(dir)))
	{
		if (ft_strcmp(dir_content->d_name, cmd) == 0)
			printf("Cmd found: %s\n", dir_content->d_name);
	}
	return (0);
}


int		ft_is_in_path(char **path, char *cmd)
{
	DIR		*dir;
	size_t	i;

	// cmd = ft_strdup("ls");
	i = 0;
	while(path[i])
	{
		dir = opendir(path[i]);
		ft_ckeck_bin(dir, cmd);
		i++;
	}
	return (0);
}
int		main(int ac, char **av)
{
	size_t	i;
	char	**line;
	char	**path;

	if (ac == 2)
	{
		i = 0;
		while (__environ[i])
		{
			line = ft_split(__environ[i], '=');
			if (ft_strcmp(line[0], "PATH") == 0)
			{
				ft_putendl_fd(line[1], 1);
				path = ft_split(line[1], ':');
				free_split(line);
				break ;
			}
			free_split(line);
			i++;
		}
	// display_path(path);
		ft_is_in_path(path, av[1]);
		free_split(path);
	}
	return (0);
}
