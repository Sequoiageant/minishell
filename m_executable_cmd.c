/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_executable_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/10 11:31:42 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"


void	ft_exec_cmd(t_list *cmd_elem, char **env_tab)
{
	t_cmd	*cmd;
	int		ret;

	cmd = (t_cmd*)cmd_elem->content;
	ft_redirs(cmd);
	if ((ret = execve(cmd->cmd_path, cmd->argv, env_tab)) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		exit(ret);
	}
}

int		ft_fork_exec_cmds(t_list *cmd_list, int **fd, char **env_tab, int num)
{
	int i;

	i = 0;
	if (fork() == 0)
	{
		dup_close_pipes(fd, 0, fd[i][PIPE_WRITE], num);
		ft_exec_cmd(cmd_list, env_tab);
	}
	cmd_list = cmd_list->next;
	while (cmd_list->next)
	{
		if (fork() == 0)
		{
			dup_close_pipes(fd, fd[i][PIPE_READ], fd[i + 1][PIPE_WRITE], num);
			ft_exec_cmd(cmd_list, env_tab);
		}
		cmd_list = cmd_list->next;
		i++;
	}
	dup_close_pipes(fd, fd[i][PIPE_READ], 0, num);
	ft_exec_cmd(cmd_list, env_tab);
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

int		ft_executable_cmd(t_list *cmd_list, t_list *env)
{
	int		status;
	int		**fd;
	char	**env_tab;
	int		num_pipe;

	env_tab = ft_list_to_tab(env);
	fd = NULL;
	g_new_pid = fork();
	num_pipe = ft_build_pipes(cmd_list, &fd);
		// mieux de faire les pipes après le premier fork: si on le fait avant le fork, on doit fermer fd[P_W] et fd[P_R] dans le current shell
	if (g_new_pid == 0)
	{
		if (num_pipe)
			ft_fork_exec_cmds(cmd_list, fd, env_tab, num_pipe);
		else
			ft_exec_cmd(cmd_list, env_tab);	
	}
	wait(&status); // doit attendre que la DERNIERE commande du pipe ait terminée // will wait for any child process -> il n'y en a juste 1 = premier fork (tous les autres fork sont faits à l'intérieur de ce child process)
	free_tab2_int(fd, num_pipe);
	ft_print_status(status);
	g_new_pid = 0;
	free_tab2(env_tab);
	return (SUCCESS);
}
