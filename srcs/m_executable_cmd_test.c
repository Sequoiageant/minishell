/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_executable_cmd_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:51:03 by grim              #+#    #+#             */
/*   Updated: 2020/07/20 16:05:32 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	ft_exec_solo_cmd(t_list *cmd_elem, char **env_tab)
{
	t_cmd	*cmd;
	int		status;

	errno = 0;
	cmd = (t_cmd*)cmd_elem->content;
	if ((g_glob.pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (g_glob.pid  == 0)
	{
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
	else
	{
		waitpid(g_glob.pid, &status, 0);
		if (WIFEXITED(status))
			g_glob.ret = WEXITSTATUS(status);
		g_glob.pid = 0;
	}
}

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
/*
void	ft_handle_pipes(t_list *cmd_list, t_list **env, char **env_tab)
{
	int		p[2];
	int		fd_in = 0;
	int		i;
	int		nb_cmd;
	int		status;

	nb_cmd = ft_lstsize(cmd_list);
	i = nb_cmd;
	while (i > 0)
	{
		pipe(p);
		if ((g_glob.pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (g_glob.pid  == 0)
		{
			dup2(fd_in, 0); //change the input according to the old one 
			if (cmd_list->next != NULL)
				dup2(p[1], 1);
			close(p[0]);
			ft_choose_builtin_or_bin(cmd_list, env, env_tab);
			exit(g_glob.ret);
		}
		else
		{
			close(p[1]);
			fd_in = p[0]; //save the input for the next command
			cmd_list = cmd_list->next;
			i--;
		}
	}
	i = 0;
	// g_glob.pid = 0;
	while (i < nb_cmd)
	{
		wait(&status);
		ft_putendl_fd("TOTO", 2);
		if (WIFEXITED(status))
			g_glob.ret = WEXITSTATUS(status);
		i++;
	}
}
*/
void		ft_handle_pipes(t_list *cmd_list, t_list **env, char **env_tab)
{
	int		status;
	int		**fd;
	int		num_pipe;
	int		i = 0;

	fd = NULL;
	num_pipe = ft_build_pipes(cmd_list, &fd);
	if ((g_glob.pid = fork()) == 0)
	{
		dup_close_pipes(fd, 0, fd[i][PIPE_WRITE], num_pipe);
		ft_choose_builtin_or_bin(cmd_list, env, env_tab);
	}
	if (cmd_list->next != NULL)
	{
		cmd_list = cmd_list->next;
		if ((g_glob.pid = fork()) == 0)
		{
			dup_close_pipes(fd, fd[i][PIPE_READ], 0, num_pipe);
			ft_choose_builtin_or_bin(cmd_list, env, env_tab);
		}
	}
	close(fd[0][1]);
	close(fd[0][0]);
	wait(&status); // doit attendre que la DERNIERE commande du pipe ait terminée // will wait for any child process -> il n'y en a juste 1 = premier fork (tous les autres fork sont faits à l'intérieur de ce child process)
	wait(&status);
	if (WIFEXITED(status))
		g_glob.ret = WEXITSTATUS(status);
	g_glob.pid = 0;
	free_tab2_int(fd, num_pipe);
}
