/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:06 by grim              #+#    #+#             */
/*   Updated: 2020/07/17 16:44:37 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_built_in(t_cmd *cmd, int index, t_list **env)
{
	t_built	built_func[NB_BLT] = {ms_echo, ms_cd, ms_pwd, ms_export,
		ms_unset, ms_env};
	int		ret;
	int		new_stdout;
	int		new_stdin;
	
	ret = FAILURE;
	// printf(">>built in\n");
	/* save STDOUT and STDIN */
	new_stdout = dup(STDOUT_FILENO);
	new_stdin = dup(STDIN_FILENO);
	/* dup some fd into STDOUT or STDIN */
	if (ft_redirs(cmd) != FAILURE) /* use this new STDOUT or STDIN */
	{
		ret = built_func[index](cmd->argc, cmd->argv, env);
		if (ret == FAILURE)
			g_glob.ret = 1;
		else
			g_glob.ret = 0;
	}
	/* restore STDOUT and STDIN */
	dup2(new_stdout, STDOUT_FILENO);
	dup2(new_stdin, STDIN_FILENO);
	close(new_stdout);
	close(new_stdin);
	return (ret);
}

int		ft_check_built_in(char *cmd, int *index)
{
	char	*built[NB_BLT] = {"echo", "cd", "pwd", "export", "unset", "env"};
	int		i;
	int		res;

	// index: index du built_in correspondant à la commande, au sein du tableau "built"
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