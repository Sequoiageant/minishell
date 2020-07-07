/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_piped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/07 16:05:58 by grim             ###   ########.fr       */
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

int		ft_piped_cmd(t_list *cmd_list, t_list **env)
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

/* Remarques concernant la commande pipe()
        fd[PIPE_READ = 0] is for input
        fd[PIPE_WRITE = 1] is for output
        [PROCESS: write(fd[PIPE_WRITE])] -> KERNEL -> [PROCESS : read(fd[PIPE_READ])]
		fd[P_W] et fd[P_R] sont dorénavant ouvert dans le current process ET dans tous les eventuels futurs child process
		ATTENTION a bien fermer les fermer tous les deux dans le current process et dans tous les eventuels child process, sinon le pipe "attend" et ca bloque le programme
*/	

int		ft_fork_pipe(char **cmd_write, char **cmd_read, t_list **env) //test avec un pipe de deux commandes
{
	int		status;
	char	*filepath[2];
	char	**env_tab;
    int     fd[2];
	int		new_pid[2];
	// cmd1 writes to STDOUT | reads from STDIN cmd 2	
	env_tab = ft_list_to_tab(*env);
	filepath[0] = ft_is_in_path(*env, cmd_write[0]);
	filepath[1] = ft_is_in_path(*env, cmd_read[0]);
	if (filepath[0] && filepath[1])
	{
		ft_strjoin_back(cmd_write[0], &filepath[0]);
		ft_strjoin_back(cmd_read[0], &filepath[1]);
		new_pid[0] = fork();
		pipe(fd); // mieux de faire le pipe après le fork
					// si on le fait avant le fork, on doit fermer fd[P_W] et fd[P_R] dans le current shell (cf lignes commentées juste avant le wait)
		if (new_pid[0] == 0)
		{
			new_pid[1] = fork();
			if (new_pid[1] == 0)
			{	
				close(fd[PIPE_READ]);
				dup2(fd[PIPE_WRITE], STDOUT_FILENO);
				close(fd[PIPE_WRITE]);
				if (execve(filepath[0], cmd_write, env_tab) == -1)
					printf(">>Exec failed\n");
			}
			else
			{
				close(fd[PIPE_WRITE]);
				dup2(fd[PIPE_READ], STDIN_FILENO);
				close(fd[PIPE_READ]);
				if (execve(filepath[1], cmd_read, env_tab) == -1)
					printf(">>Exec failed\n");
			}
		}
		else
		{
			close(fd[PIPE_WRITE]);
			close(fd[PIPE_READ]);
			wait(&status);
		}
	}
	else
	{
		ft_putstr_fd("Command(s) not found: ", 1);
		if (filepath[0] == NULL)
			ft_putendl_fd(cmd_write[0], 1);
		if (filepath[1] == NULL)
			ft_putendl_fd(cmd_write[0], 1);
	}
	free(filepath[0]);
	free_tab2(env_tab);
	free(filepath[1]);
	return (0);
}