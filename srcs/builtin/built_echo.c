/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:34 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 10:48:39 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static void	ms_echo_suite(int argc, char *argv[], int num_opt)
{
	int i;

	i = num_opt + 1;
	while (i < argc - 1)
	{
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd(argv[i], 1);
	if (num_opt == 0)
		ft_putstr_fd("\n", 1);
}

static int	is_option(char *str)
{
	int i;

	if (str[0] != '-')
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	count_options(char *argv[])
{
	int count;
	int i;

	i = 1;
	count = 0;
	while (argv[i])
	{
		if (is_option(argv[i]))
		{
			count++;
			i++;
		}
		else
			return (count);
	}
	return (count);
}

int			ms_echo(int argc, char *argv[], t_list **env)
{
	int	num_opt;

	(void)env;
	if (argc == 1)
	{
		ft_putstr_fd("\n", 1);
		return (SUCCESS);
	}
	num_opt = count_options(argv);
	if (num_opt && argc == num_opt + 1)
		return (SUCCESS);
	ms_echo_suite(argc, argv, num_opt);
	return (SUCCESS);
}
