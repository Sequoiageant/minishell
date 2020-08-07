/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:12:14 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/07 10:05:27 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	cd_home_not_set(t_key_val *key)
{
	if (key)
		return (SUCCESS);
	else
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (FAILURE);
	}
}

int	cd_too_many_args()
{
	ft_putstr_fd("bash: cd: too many arguments\n", 2);
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
