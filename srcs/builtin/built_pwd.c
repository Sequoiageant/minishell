/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/06 09:26:12 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	ms_pwd(int argc, char *argv[], t_list **env)
{
	char	*path;
	int		ret;

	(void)argc;
	(void)argv;
	(void)env;
	ret = SUCCESS;
	path = getcwd(NULL, 0);
	if (path)
	{
		if (write(1, path, ft_strlen(path)) == -1)
			ret = FAILURE;
		if (write(1, "\n", 1) == -1)
			ret = FAILURE;
		free(path);
		path = NULL;
	}
	else
	{
		put_err("pwd: ", NULL, "Current directory not found", TRUE);
		ret = FAILURE;
	}
	return (ret);
}
