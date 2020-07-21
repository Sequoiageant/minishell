/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_executable_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/21 16:54:53 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"


void	ft_exec_cmd(t_list *cmd_elem, char **env_tab)
{
	t_cmd	*cmd;

	errno = 0;
	cmd = (t_cmd*)cmd_elem->content;
	if (ft_redirs(cmd) != FAILURE)
	{
		if (cmd->cmd_path)
			execve(cmd->cmd_path, cmd->argv, env_tab);
		if (!cmd->cmd_path || errno == 2)
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		if (errno == 13)
		{
			put_err(cmd->argv[0], NULL, ": Permission denied", TRUE);
			exit(126);
		}
	}
	else
		exit(g_glob.ret);
}

int		ft_executable_cmd(t_list *cmd_list, t_list *env)
{
	int		status;
	int		**fd;
	char	**env_tab;
	int		num_pipe;
	int		i = 0;
	int		firtst_pid;

	env_tab = ft_list_to_tab(env);
	fd = NULL;
	num_pipe = ft_build_pipes(cmd_list, &fd);
	firtst_pid = fork();
	if (cmd_list->next == NULL)
		g_glob.pid = firtst_pid;
	if (firtst_pid == 0)
	{
		if (cmd_list->next)
			dup_close_pipes(fd, 0, fd[i][PIPE_WRITE], num_pipe);
		ft_choose_builtin_or_bin(cmd_list, &env, env_tab);
	}
	cmd_list = cmd_list->next;
	if (cmd_list)
	{
		while (cmd_list->next)
		{
			if (fork() == 0)
			{
				dup_close_pipes(fd, fd[i][PIPE_READ], fd[i + 1][PIPE_WRITE], num_pipe);
				ft_choose_builtin_or_bin(cmd_list, &env, env_tab);
			}
			cmd_list = cmd_list->next;
			i++;
		}
		if ((g_glob.pid = fork()) == 0)
		{
			dup_close_pipes(fd, fd[i][PIPE_READ], 0, num_pipe);
			ft_choose_builtin_or_bin(cmd_list, &env, env_tab);
		}
	}
	i = 0;
	while (i < num_pipe)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;
	}
	i = 0;
	while (i < num_pipe + 1)
	{
		if (wait(&status) == g_glob.pid)
			if (WIFEXITED(status))
				g_glob.ret = WEXITSTATUS(status);
		i++;
	}
	g_glob.pid = 0;
	free_tab2_int(fd, num_pipe);
	free_tab2(env_tab);
	return (SUCCESS);
}

/*
		Remarques concernant la commande pipe()
        fd[PIPE_READ = 0] is for input
        fd[PIPE_WRITE = 1] is for output
        [PROCESS: write(fd[PIPE_WRITE])] -> KERNEL -> [PROCESS : read(fd[PIPE_READ])]
		fd[P_W] et fd[P_R] sont dorénavant ouvert dans le current process ET dans tous les eventuels futurs child process
		ATTENTION a bien fermer les fermer tous les deux dans le current process et dans tous les eventuels child process, sinon le pipe "attend" et ca bloque le programme
*/