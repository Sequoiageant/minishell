/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:06 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 20:15:55 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_built_in(char **cmd, int argc, int index, t_list **env)
{
	t_built	built_func[] = {ms_echo, ms_cd}; // ,ms_pwd, ms_export, ms_unset, ms_env, ms_exit};
	int		ret;

	printf("built in\n");
	ret = 0;
	if (index < 2)
		ret = built_func[index](argc, cmd, env);
	else
		ft_putstr_fd("function not written yet\n", 1);
	return (ret);
}

int		ft_check_built_in(char *cmd, int *index)
{
	char			*built[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int				i;
	int				res;

	// index: index du built_in correspondant à la commande, au sein du tableau "built"
	i = 0;
	while (built[i])
	{
		if ((res = ft_strcmp(cmd, built[i]) == 0))
		{
			*index = i;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}