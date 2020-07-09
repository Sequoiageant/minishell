/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_simple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:09 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 15:07:11 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"


int		ft_simple_cmd_fork(char **cmd, t_list **env, char *filepath)
{
	int		status;
	char	**env_tab;
	int		ret;
	
	ret = 0;
	env_tab = ft_list_to_tab(*env);
	g_new_pid = fork();
	if (g_new_pid == 0)
	{
		printf("filepath: %s\n", filepath);
		if ((ret = execve(filepath, cmd, env_tab) == -1))
			ft_putendl_fd("Command not found", 2);
		exit(ret); //Pour exit du processus dans la cas d'un fail de execve
	}
	else // pas necessaire je pense de mettre un else, car dans tous les cas le child process ne "sort" pas du if()
	{
		waitpid(g_new_pid, &status, 0);
		// Le code qui suit vient du man wait2, à visée de debug ou d'indication, à voir !
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
	}
	free_tab2(env_tab); // a mettre en bas je pense, sinon ne sera pas exec
	return (0);
}
