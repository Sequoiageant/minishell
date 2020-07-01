/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:06 by grim              #+#    #+#             */
/*   Updated: 2020/07/01 20:24:22 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_built_in(char **cmd, int argc, int index, t_list **env)
{
	t_built	built_func[] = {ms_echo, ms_cd}; // ,ms_pwd, ms_export, ms_unset, ms_env, ms_exit};
	int		ret;

	ret = 0;
	if (index < 2)
		ret = built_func[index](argc, cmd, env);
	else
		ft_putstr_fd("function not written yet\n", 1);
	return (ret);
}