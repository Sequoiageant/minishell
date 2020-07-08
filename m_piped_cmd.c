/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_piped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/08 11:30:35 by grim             ###   ########.fr       */
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

int		ft_dup_exec_read(char **cmd, t_list *env, int fd[2], char **env_tab)
{
	char *filepath;
	
	filepath = find_in_env_path(env, cmd[0]);
	if (!filepath)
	{
		ft_putstr_fd("Cmd not found:", 1);
		ft_putendl_fd(cmd[0], 1);
		close(fd[PIPE_WRITE]);
		close(fd[PIPE_READ]);
		return(SUCCESS);
	}
	ft_strjoin_back(cmd[0], &filepath);
	close(fd[PIPE_WRITE]);
	dup2(fd[PIPE_READ], STDIN_FILENO);
	close(fd[PIPE_READ]);
	if (execve(filepath, cmd, env_tab) == -1)
		printf(">>Exec failed\n");
	free(filepath);
	return (SUCCESS);
}

int		ft_dup_exec_write(char **cmd, t_list *env, int fd[2], char **env_tab)
{
	char *filepath;
	
	filepath = find_in_env_path(env, cmd[0]);
	if (!filepath)
	{
		ft_putstr_fd("Cmd not found:", 1);
		ft_putendl_fd(cmd[0], 1);
		close(fd[PIPE_READ]);
		close(fd[PIPE_WRITE]);
		return(SUCCESS);
	}
	ft_strjoin_back(cmd[0], &filepath);
	close(fd[PIPE_READ]);
	dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	close(fd[PIPE_WRITE]);
	if (execve(filepath, cmd, env_tab) == -1)
		printf(">>Exec failed\n");
	free(filepath);
	return (SUCCESS);
}

int		ft_fork_pipe(char **cmd_write, char **cmd_read, t_list *env)
{
	int		status;
    int     fd[2];
	int		new_pid[2];
	char	**env_tab;
		
	env_tab = ft_list_to_tab(env);
	new_pid[0] = fork();
	if (new_pid[0] == 0)
	{
		pipe(fd); // mieux de faire le pipe après le premier fork: si on le fait avant le fork, on doit fermer fd[P_W] et fd[P_R] dans le current shell
		new_pid[1] = fork();
		if (new_pid[1] == 0)
			ft_dup_exec_write(cmd_write, env, fd, env_tab);
		else
			ft_dup_exec_read(cmd_read, env, fd, env_tab);
	}
	else
		wait(&status); // doit attendre que la DERNIERE commande du pipe ait terminée
		// will wait for any child process -> il n'y en a juste 1 = premier fork (tous les autres fork sont faits à l'intérieur de ce child process)
	free_tab2(env_tab);
	return (SUCCESS);
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
    cmd1 = (t_cmd*)cmd_list->content;
    cmd_list = cmd_list->next;
    cmd2 = (t_cmd*)cmd_list->content;
    if (cmd_list->next)
    {
        printf("Pipe cmd with more than 2 cmds: not ready yet");
        return (SUCCESS);
    }
    printf("Piped cmd\n");
    ft_fork_pipe(cmd1->argv, cmd2->argv, env);
    return (SUCCESS);
}
