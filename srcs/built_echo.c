/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:34 by grim              #+#    #+#             */
/*   Updated: 2020/07/16 11:02:14 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	ms_echo_suite(int argc, char *argv[], int i, int n_opt)
{
	while (i < argc - 1)
	{
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd(argv[i], 1);
	if (n_opt == FALSE)
		ft_putstr_fd("\n", 1);
}

int		ms_echo(int argc, char *argv[], t_list **env)
{
	int	i;
	int	n_opt;

	(void)env;
	i = 1;
	n_opt = FALSE;
	if (argc == 1)
	{
		ft_putstr_fd("\n", 1);
		return (SUCCESS);
	}
	if (ft_strncmp(argv[1], "-n", 2) == 0)
	{
		i = 2;
		n_opt = TRUE;
	}
	if (n_opt && argc == 2)
		return (SUCCESS);
	ms_echo_suite(argc, argv, i, n_opt);
	return (SUCCESS);
}
