/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:53:25 by grim              #+#    #+#             */
/*   Updated: 2020/07/15 16:00:37 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void    ft_print_status(int status)
{
	if (WIFEXITED(status)) {
		printf("terminé, code=%d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("tué par le signal %d\n", WTERMSIG(status));
	} else if (WIFSTOPPED(status)) {
		printf("arrêté par le signal %d\n", WSTOPSIG(status));
	} else if (WIFCONTINUED(status)) {
		printf("relancé\n");
	}
}

void	put_err(char *cmd, char *arg, char *last)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	if (last)
		ft_putendl_fd(last, 2);
}
