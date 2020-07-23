/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:34 by grim              #+#    #+#             */
/*   Updated: 2020/07/23 14:47:17 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	ms_echo_suite(int argc, char *argv[], int num_opt)
{
	int i;

	i = num_opt + 1;
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], "?") == 0)
			ft_putnbr_fd(g_glob.ret, 1);
		else
			ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(" ", 1);

		i++;
	}
	if (ft_strcmp(argv[i], "?") == 0)
		ft_putnbr_fd(g_glob.ret, 1);
	else
		ft_putstr_fd(argv[i], 1);
	if (num_opt == 0) // pas de "-n"
		ft_putstr_fd("\n", 1);
}


int		is_option(char *str)
{
	int i;

	if (str[0] != '-')
		return(FALSE);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		count_options(char *argv[])
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

int		ms_echo(int argc, char *argv[], t_list **env)
{
	int	num_opt; // nombre d'arguments de type "-n"
	
	(void)env;
	if (argc == 1) // pas de "-n" et pas d'argument
	{
		ft_putstr_fd("\n", 1);
		return (SUCCESS);
	}
	num_opt = count_options(argv);
	// printf("num opt: %d\n", num_opt);
	if (num_opt && argc == num_opt + 1) // si une/plusieurs options de type "-n" et pas d'argument
		return (SUCCESS);
	ms_echo_suite(argc, argv, num_opt);
	return (SUCCESS);
}
