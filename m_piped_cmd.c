/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_piped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/04 18:24:53 by julnolle         ###   ########.fr       */
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

int		ft_fork_pipe(char **cmd1, char **cmd2, t_list **env) //test avec un pipe de deux commandes
{
	int		status;
	char	*filepath1;
	char	*filepath2;
	char	**env_tab;
    int     fd[2];
	
	env_tab = ft_list_to_tab(*env);
	pipe(fd);
        // fd[0] is for input
        // fd[1] is for output
        // both are now open: fd[0] for reading and fd[1] for writing
        // [PROCESS : write(fd[1])] -> KERNEL -> [PROCESS : read(fd[0])]
	
	filepath1 = find_in_env_path(*env, cmd1[0]);
	filepath2 = find_in_env_path(*env, cmd2[0]);
	if (filepath1 && filepath2)
	{
		if ((g_new_pid = fork()) == -1)
		{
			perror("fork");
			return (FAILURE);
		}
		if (g_new_pid == 0)
		{
			printf("inside child process\n");
			ft_strjoin_back(cmd1[0], &filepath1);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (execve(filepath1, cmd1, env_tab) == -1)
				printf(">>Exec failed\n");
		}
		else
		{
		// old process
			waitpid(g_new_pid, &status, 0);
			// (void)status;
			printf("inside parent process\n");
			ft_strjoin_back(cmd2[0], &filepath2);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (execve(filepath2, cmd2, env_tab) == -1)
				printf(">>Exec failed\n");
			
		// return (g_new_pid);
		}
	}
	else
	{
		ft_putstr_fd("Command(s) not found: ", 1);
		if (filepath1 == NULL)
			ft_putendl_fd(cmd1[0], 1);
		if (filepath2 == NULL)
			ft_putendl_fd(cmd2[0], 1);
	}
	free(filepath1);
	free_tab2(env_tab);
	free(filepath2);
	return (0);
}