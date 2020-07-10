/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:14:58 by grim              #+#    #+#             */
/*   Updated: 2020/07/10 11:44:42 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

pid_t	g_new_pid;

int		ft_handle(char *buf, t_list **env)
{
	t_list	*pipe_list;

	pipe_list = NULL;
	if (ft_parse(buf, *env, &pipe_list) == FAILURE)
		return(FAILURE);
	ft_traitement(pipe_list, env);
	ft_lstclear(&pipe_list, &del_pipe);
	return (SUCCESS);
}

void	handle_ctrlc(int signum)
{
	if (g_new_pid && signum == SIGINT)
	{
		kill(g_new_pid, signum);
		ft_putchar_fd('\n', 1);
		g_new_pid = 0;
	}
	else
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("cmd: ", 1);
	}
}

void	handle_ctrlback(int signum)
{
	if (g_new_pid && signum == SIGQUIT)
	{
		kill(g_new_pid, signum);
		ft_putendl_fd("quit (core dumped)", 2);
		ft_putstr_fd("cmd: ", 1);
		g_new_pid = 0;
	}
	else
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("cmd: ", 1);
	}
}

int		main()
{
	t_list	*env;
	char	*buf;

	ft_init(&env);
	if (signal(SIGINT, handle_ctrlc) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, handle_ctrlback) == SIG_ERR)
		return (1);
	ft_putstr_fd("cmd: ", 1);
	while (get_next_line(0, &buf) > 0)
	{
		ft_handle(buf, &env);
		free(buf);
		ft_putstr_fd("cmd: ", 1);
	}
	ft_lstclear(&env, &del_key_val);
	ft_putendl_fd("exit", 1);
	return (0);
}
