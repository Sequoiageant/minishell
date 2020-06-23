/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:06 by grim              #+#    #+#             */
/*   Updated: 2020/06/23 15:02:43 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_built_in(char **cmd, int argc, int index, t_list **env)
{
	t_built	built_func[] = {ms_echo, ms_cd}; // ,ms_pwd, ms_export, ms_unset, ms_env, ms_exit};
	int		ret;
	char *cwd = NULL;

	if (index < 2)
	{
		// printf("pre-pwd: %s\n", getenv("PWD"));
		// printf("pre-getcwd: %s\n", getcwd(cwd, 200));
		ret = built_func[index](argc, cmd, env);
		// printf("post-pwd: %s\n", getenv("PWD"));
		printf("post-getcwd: %s\n", getcwd(cwd, 200));
		// free(cwd);
	}
	else
		ft_putstr_fd("function not written yet\n", 1);
	return (ret);
}