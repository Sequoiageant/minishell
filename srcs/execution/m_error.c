/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:53:25 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 19:50:49 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	put_err(char *cmd, char *arg, char *last, int minishell)
{
	if (minishell)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	if (last)
		ft_putendl_fd(last, STDERR_FILENO);
}
