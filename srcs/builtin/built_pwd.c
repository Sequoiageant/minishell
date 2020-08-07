/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/07 11:42:32 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	ms_pwd(int argc, char *argv[], t_list **env)
{
	char	*path;
	int		ret;

	(void)argc;
	(void)argv;
	ret = SUCCESS;
	if ((path = getcwd(NULL, PATH_MAX)))
	{
		ft_putendl_fd(path, 1);
		free(path);
		path = NULL;
	}
	else if ((path = find_env_val(*env, "PWD")))
		ft_putendl_fd(path, 1);
	else
	{
		put_err("pwd: ", NULL, "Current directory not found", TRUE);
		ret = FAILURE;
	}
	return (ret);
}
