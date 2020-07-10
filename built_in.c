/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:06 by grim              #+#    #+#             */
/*   Updated: 2020/07/10 14:33:39 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_built_in(t_cmd *cmd, int index, t_list **env)
{
	t_built	built_func[NB_BLT] = {ms_echo, ms_cd, ms_pwd, ms_export,
		ms_unset, ms_env, ms_exit};
	int		ret;
	int		new_stdout;
	int		new_stdin;
	
	printf(">>built in\n");
	/* save STDOUT and STDIN */
	new_stdout = dup(STDOUT_FILENO);
	new_stdin = dup(STDIN_FILENO);
	/* dup some fd into STDOUT or STDIN */
	ft_redirs(cmd);
	/* use this new STDOUT or STDIN */
	ret = built_func[index](cmd->argc, cmd->argv, env);
	/* restore STDOUT and STDIN */
	dup2(new_stdout, STDOUT_FILENO);
	dup2(new_stdin, STDIN_FILENO);
	close(new_stdout);
	close(new_stdin);
	return (ret);
}

int		ft_check_built_in(char *cmd, int *index)
{
	char	*built[NB_BLT] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
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