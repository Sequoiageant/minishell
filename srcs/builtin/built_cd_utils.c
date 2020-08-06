/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:12:14 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 09:25:49 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	cd_home_not_set(t_key_val *key, char *old_pwd)
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
	ft_putstr_fd("bash: cd: too many arguments\n", 2);
	free(old_pwd);
	old_pwd = NULL;
	return (FAILURE);
}

int	cd_back_to_oldpwd(t_list *env)
{
	t_key_val *oldpwd;

	if ((oldpwd = find_key_val(env, "OLDPWD")) == NULL)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		return (FAILURE);
	}
	else
	{
		ft_putendl_fd(oldpwd->val, 1);
		return (chdir(oldpwd->val));
	}
}
