/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:06 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 09:26:09 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int		ft_built_in(t_cmd *cmd, int index, t_list **env)
{
	int				ret;
	int				new_stdout;
	int				new_stdin;
	static t_built	built_func[NB_BLT] = {ms_echo, ms_cd, ms_pwd, ms_export,
		ms_unset, ms_env};

	ret = FAILURE;
	new_stdout = dup(STDOUT_FILENO);
	new_stdin = dup(STDIN_FILENO);
	if (ft_redirs(cmd) != FAILURE)
	{
		ret = built_func[index](cmd->argc, cmd->argv, env);
		if (ret == FAILURE)
			g_glob.ret = 1;
		else
			g_glob.ret = 0;
	}
	dup2(new_stdout, STDOUT_FILENO);
	dup2(new_stdin, STDIN_FILENO);
	close(new_stdout);
	close(new_stdin);
	return (ret);
}

int		ft_check_built_in(char *cmd, int *index)
{
	int			i;
	int			res;
	static char	*built[NB_BLT] = {"echo", "cd", "pwd", "export",
	"unset", "env"};

	i = 0;
	while (i < NB_BLT)
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
