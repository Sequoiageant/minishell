/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_piped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/08 15:10:13 by grim             ###   ########.fr       */
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
// int		ft_dup_exec_read(char **cmd, t_list *env, int fd[2], char **env_tab)
// {
// 	char *filepath;
	
// 	filepath = find_in_env_path(env, cmd[0]);
// 	if (!filepath)
// 	{
// 		ft_putstr_fd("Cmd not found:", 1);
// 		ft_putendl_fd(cmd[0], 1);
// 		return(SUCCESS);
// 	}
// 	ft_strjoin_back(cmd[0], &filepath);
// 	dup2(fd[PIPE_READ], STDIN_FILENO);
// 	if (execve(filepath, cmd, env_tab) == -1)
// 		printf(">>Exec failed\n");
// 	return (SUCCESS);
// }

// FILEPATH n'est pas FREE
int		ft_dup_exec(char **cmd, t_list *env, int fd_in, int fd_out, char **env_tab)
{
	char *filepath;
	
	filepath = find_in_env_path(env, cmd[0]);
	if (!filepath)
	{
		ft_putstr_fd("Cmd not found:", 1);
		ft_putendl_fd(cmd[0], 1);
		return(SUCCESS);
	}
	ft_strjoin_back(cmd[0], &filepath);
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
	if (execve(filepath, cmd, env_tab) == -1)
		printf(">>Exec failed\n");
	return (SUCCESS);
}

void	close_pipes(int fd1[2], int fd2[2])
{
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
}

int		ft_fork_pipe(char **cmd1, char **cmd2, char **cmd3, t_list *env)
{
	int		status;
    int     fd1[2];
    int     fd2[2];
	int		new_pid[3];
	char	**env_tab;
		
	env_tab = ft_list_to_tab(env);
	new_pid[0] = fork();
	if (new_pid[0] == 0)
	{
		pipe(fd1); // mieux de faire le pipe après le premier fork: si on le fait avant le fork, on doit fermer fd[P_W] et fd[P_R] dans le current shell
		pipe(fd2);
		new_pid[1] = fork();
		if (new_pid[1] == 0)
		{
			close(fd1[0]);
			close(fd1[1]);
			close(fd2[PIPE_READ]);
			ft_dup_exec(cmd1, env, 0, fd2[PIPE_WRITE], env_tab);
		}
		new_pid[2] = fork();
		if (new_pid[2] == 0)
		{
			close(fd1[PIPE_READ]);
			close(fd2[PIPE_WRITE]);
			ft_dup_exec(cmd2, env, fd2[PIPE_READ], fd1[PIPE_WRITE], env_tab);
		}
		if (new_pid[1] && new_pid[2])
		{
			close(fd1[PIPE_WRITE]);
			close(fd2[0]);
			close(fd2[1]);
			ft_dup_exec(cmd3, env, fd1[PIPE_READ], 0, env_tab);
		}
	}
	else
	{
		wait(&status); // doit attendre que la DERNIERE commande du pipe ait terminée
		// will wait for any child process -> il n'y en a juste 1 = premier fork (tous les autres fork sont faits à l'intérieur de ce child process)
		free_tab2(env_tab);
		printf("surprise\n");
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


int		ft_piped_cmd(t_list *cmd_list, t_list *env)
{
    t_cmd *cmd1;
    t_cmd *cmd2;
    t_cmd *cmd3;
	
    cmd1 = (t_cmd*)cmd_list->content;
    cmd_list = cmd_list->next;
    cmd2 = (t_cmd*)cmd_list->content;
    cmd_list = cmd_list->next;
    cmd3 = (t_cmd*)cmd_list->content;
    if (cmd_list->next)
    {
        printf("Pipe cmd with more than 2 cmds: not ready yet");
        return (SUCCESS);
    }
    printf("Piped cmd\n");
    ft_fork_pipe(cmd1->argv, cmd2->argv, cmd3->argv, env);
    return (SUCCESS);
}
