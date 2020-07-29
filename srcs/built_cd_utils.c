/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:12:14 by grim              #+#    #+#             */
/*   Updated: 2020/07/29 18:26:10 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	cd_handle_home(t_key_val *key, char *old_pwd)
{
	free(old_pwd);
	old_pwd = NULL;
	if (key)
		return (SUCCESS);
	else
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (FAILURE);
	}
}

int	cd_too_many_args(char *old_pwd)
{
	ft_putstr_fd("bash: cd: too many arguments\n", 1);
	free(old_pwd);
	old_pwd = NULL;
	return (FAILURE);
}
