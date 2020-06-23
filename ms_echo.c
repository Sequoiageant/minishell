/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:34 by grim              #+#    #+#             */
/*   Updated: 2020/06/23 14:04:47 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

// ajouter le main si on veut créer l'executable
// ne gère pas le retour d'erreur (en cas d'erreur de write)

int	ms_echo(int argc, char *argv[])
{
	int	i;
	int	n_opt;

	i = 1;
	n_opt = FALSE;
	// printf("argc: %d\n", argc);
	if (argc == 1)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (ft_strncmp(argv[1], "-n", 2) == 0)
	{
		i = 2;
		n_opt = TRUE;
	}
	if (n_opt && argc == 2)
		return (0);
	while (i < argc - 1)
	{
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd(argv[i], 1);
	if (n_opt == FALSE)
		ft_putstr_fd("\n", 1);
	return (1);
}

// int main(int argc, char **argv)
// {
//     ms_echo(argc, argv);
// }
