/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_piped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/08 22:09:38 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int contains_pipe(t_list *cmd_list)
{
    if (cmd_list->next)
        return (TRUE);
    else
        return (FALSE);
}

// FILEPATH n'est pas FREE
int		ft_exec_cmd(t_list *cmd_elem, char **env_tab, t_list *env)
{
	char *filepath;
	t_cmd *cmd;

	cmd = (t_cmd*)cmd_elem->content;
	filepath = find_in_env_path(env, cmd->argv[0]);
	if (!filepath)
	{
		ft_putstr_fd("Cmd not found:", 1);
		ft_putendl_fd(cmd->argv[0], 1);
		return(SUCCESS);
	}
	ft_strjoin_back(cmd->argv[0], &filepath);
	if (execve(filepath, cmd->argv, env_tab) == -1)
		printf(">>Exec failed\n");
	return (SUCCESS);
}

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

int		ft_build_pipes(t_list *cmd_list, int ***fd)
{
	int num_cmd;
	int i;

	num_cmd = 0;
	while (cmd_list)
	{
		num_cmd++;
		cmd_list = cmd_list->next;
	}
	*fd = malloc((num_cmd - 1) * sizeof(**fd));
	i = 0;
	while (i < num_cmd - 1)
	{
		(*fd)[i] = malloc(2 * sizeof(int));
		if (pipe((*fd)[i]) == -1)
			printf("Error pipe\n");
		i++;
	}
	return (i);
}

int		ft_fork_exec_cmds(t_list *cmd_list, int **fd, char **env_tab, t_list *env, int num)
{
	int i;
	int new_pid;

	i = 0;	
	new_pid = fork();
	if (new_pid == 0)
	{
		dup_close_pipes(fd, 0, fd[i][PIPE_WRITE], num);
		ft_exec_cmd(cmd_list, env_tab, env);
	}
	else
	{	
		cmd_list = cmd_list->next;
		while (cmd_list->next)
		{
			if (fork() == 0)
			{
				dup_close_pipes(fd, fd[i][PIPE_READ], fd[i + 1][PIPE_WRITE], num);
				ft_exec_cmd(cmd_list, env_tab, env);
			}
			cmd_list = cmd_list->next;
			i++;
		}
		dup_close_pipes(fd, fd[i][PIPE_READ], 0, num);
		ft_exec_cmd(cmd_list, env_tab, env);
	}
	return (SUCCESS);	
}

int		ft_piped_cmd(t_list *cmd_list, t_list *env)
{
	int		status;
    int     **fd;
	int		fd1[2];
	int		new_pid;
	char	**env_tab;
	int		num_pipe;
		
	env_tab = ft_list_to_tab(env);
	new_pid = fork();
	pipe(fd1);
	if (new_pid == 0)
	{
		num_pipe = ft_build_pipes(cmd_list, &fd);
		// mieux de faire les pipes après le premier fork: si on le fait avant le fork, on doit fermer fd[P_W] et fd[P_R] dans le current shell
		ft_fork_exec_cmds(cmd_list, fd, env_tab, env, num_pipe);	
	}
	else
	{
		wait(&status); // doit attendre que la DERNIERE commande du pipe ait terminée
		// will wait for any child process -> il n'y en a juste 1 = premier fork (tous les autres fork sont faits à l'intérieur de ce child process)
		free_tab2(env_tab);
	}
	return(SUCCESS);
}


/* Remarques concernant la commande pipe()
        fd[PIPE_READ = 0] is for input
        fd[PIPE_WRITE = 1] is for output
        [PROCESS: write(fd[PIPE_WRITE])] -> KERNEL -> [PROCESS : read(fd[PIPE_READ])]
		fd[P_W] et fd[P_R] sont dorénavant ouvert dans le current process ET dans tous les eventuels futurs child process
		ATTENTION a bien fermer les fermer tous les deux dans le current process et dans tous les eventuels child process, sinon le pipe "attend" et ca bloque le programme
*/	