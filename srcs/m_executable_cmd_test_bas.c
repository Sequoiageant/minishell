/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_executable_cmd_test_bas.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/20 12:57:29 by grim             ###   ########.fr       */
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
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			exit(126);
		}
	}
	else
		exit(g_glob.ret);
}

// int		ft_fork_exec_cmds(t_list *cmd_list, int **fd, char **env_tab, int num)
// {
// 	int i;

// 	i = 0;
// 	if (fork() == 0)
// 	{
// 		dup_close_pipes(fd, 0, fd[i][PIPE_WRITE], num);
// 		ft_exec_cmd(cmd_list, env_tab);
// 	}
// 	cmd_list = cmd_list->next;
// 	while (cmd_list->next)
// 	{
// 		if (fork() == 0)
// 		{
// 			dup_close_pipes(fd, fd[i][PIPE_READ], fd[i + 1][PIPE_WRITE], num);
// 			ft_exec_cmd(cmd_list, env_tab);
// 		}
// 		cmd_list = cmd_list->next;
// 		i++;
// 	}
// 	dup_close_pipes(fd, fd[i][PIPE_READ], 0, num);
// 	ft_exec_cmd(cmd_list, env_tab);
// 	return (SUCCESS);
// }

/*
		Remarques concernant la commande pipe()
        fd[PIPE_READ = 0] is for input
        fd[PIPE_WRITE = 1] is for output
        [PROCESS: write(fd[PIPE_WRITE])] -> KERNEL -> [PROCESS : read(fd[PIPE_READ])]
		fd[P_W] et fd[P_R] sont dorénavant ouvert dans le current process ET dans tous les eventuels futurs child process
		ATTENTION a bien fermer les fermer tous les deux dans le current process et dans tous les eventuels child process, sinon le pipe "attend" et ca bloque le programme
*/

int		ft_executable_cmd(t_list *cmd_list, t_list *env)
{
	int		status;
	int		**fd;
	char	**env_tab;
	int		num_pipe;
	int		i = 0;

	env_tab = ft_list_to_tab(env);
	fd = NULL;
	num_pipe = ft_build_pipes(cmd_list, &fd);
	if ((g_glob.pid = fork()) == 0)
	{
		dup_close_pipes(fd, 0, fd[i][PIPE_WRITE], num_pipe);
		ft_exec_cmd(cmd_list, env_tab);
	}
	cmd_list = cmd_list->next;
	if ((g_glob.pid = fork()) == 0)
	{
		dup_close_pipes(fd, fd[i][PIPE_READ], 0, num_pipe);
		ft_exec_cmd(cmd_list, env_tab);
	}
	close(fd[0][1]);
	close(fd[0][0]);
	wait(&status); // doit attendre que la DERNIERE commande du pipe ait terminée // will wait for any child process -> il n'y en a juste 1 = premier fork (tous les autres fork sont faits à l'intérieur de ce child process)
	wait(&status);
	if (WIFEXITED(status))
		g_glob.ret = WEXITSTATUS(status);
	g_glob.pid = 0;
	free_tab2_int(fd, num_pipe);
	free_tab2(env_tab);
	return (SUCCESS);
}
