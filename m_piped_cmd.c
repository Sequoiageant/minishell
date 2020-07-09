/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_piped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 15:40:40 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	dup_close_pipes(int *fd[2], int fd_in, int fd_out, int num)
{
	int i;

	if (fd_out)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (fd_in)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	i = 0;
	while (i < num)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	ft_exec_cmd(t_list *cmd_elem, char **env_tab)
{
	t_cmd	*cmd;
	char	*filepath;
	int		ret;

	cmd = (t_cmd*)cmd_elem->content;
	filepath = cmd->cmd_path;
	if ((ret = execve(filepath, cmd->argv, env_tab)) == -1)
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

int		ft_piped_cmd(t_list *cmd_list, t_list *env)
{
	int		status;
	int		**fd;
	char	**env_tab;
	int		num_pipe;

	env_tab = ft_list_to_tab(env);
	g_new_pid = fork();
	if (g_new_pid == 0)
	{
		num_pipe = ft_build_pipes(cmd_list, &fd);
		// mieux de faire les pipes après le premier fork: si on le fait avant le fork, on doit fermer fd[P_W] et fd[P_R] dans le current shell
		ft_fork_exec_cmds(cmd_list, fd, env_tab, num_pipe);
	}
	wait(&status); // doit attendre que la DERNIERE commande du pipe ait terminée // will wait for any child process -> il n'y en a juste 1 = premier fork (tous les autres fork sont faits à l'intérieur de ce child process)
	if (WIFEXITED(status)) {
		printf("terminé, code=%d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("tué par le signal %d\n", WTERMSIG(status));
	} else if (WIFSTOPPED(status)) {
		printf("arrêté par le signal %d\n", WSTOPSIG(status));
	} else if (WIFCONTINUED(status)) {
		printf("relancé\n");
	}
	g_new_pid = 0;
	free_tab2(env_tab);
	return (SUCCESS);
}
