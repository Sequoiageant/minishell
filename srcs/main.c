/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:14:58 by grim              #+#    #+#             */
/*   Updated: 2020/07/29 18:27:48 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

t_globale	g_glob;

int		ft_handle(char *buf, t_list **env)
{
	t_list	*pipe_list;

	pipe_list = NULL;
	if (ft_parse(buf, *env, &pipe_list) == FAILURE)
	{
		ft_str_free(&buf);
		return(FAILURE);
	}
	ft_str_free(&buf);
	ft_traitement(pipe_list, env);
	ft_lstclear(&pipe_list, &del_pipe);
	return (SUCCESS);
}

void	signal_handler(int signum)
{
	if (g_glob.pid && signum == SIGINT)
	{
		kill(g_glob.pid, signum);
		ft_putchar_fd('\n', 1);
		g_glob.pid = 0;
	}
	else if (g_glob.pid && signum == SIGQUIT)
	{
		kill(g_glob.pid, signum);
		ft_putendl_fd("Quit (core dumped)", 2);
		g_glob.pid = 0;
	}
	else
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("cmd: ", 1);
	}
	if (signum == SIGINT)
		g_glob.ret = CTRLC_RET;
	if (signum == SIGQUIT)
		g_glob.ret = CTRLBACK_RET;
}

void	ft_shell_init(t_list **env)
{
	char	*tmp;
	char	*path;
	int		nb;

	tmp = NULL;
	path = getcwd(NULL, 0);
	if (path)
		change_env_val(env, "SHELL", path);
	else
		put_err(NULL, NULL, "Shell directory not found", TRUE);
	if ((tmp = find_env_val(*env, "SHLVL")))
		nb = ft_atoi(tmp) + 1;
	else
		nb = 1;
	tmp = ft_itoa(nb);
	if (is_key_in_env(*env, "SHLVL"))
		change_env_val(env, "SHLVL", tmp);
	else
		add_keyval_to_env(ft_strdup("SHLVL"), tmp, env);
}

int		main(void)
{
	t_list	*env;
	char	*buf;

	ft_init(&env);
	ft_shell_init(&env);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		return (1);
	ft_putstr_fd("cmd: ", 1);
	while (get_next_line(0, &buf) > 0)
	{
		ft_handle(buf, &env);
		ft_putstr_fd("cmd: ", 1);
	}
	ft_str_free(&buf);
	ft_lstclear(&env, &del_key_val);
	ft_putendl_fd("exit", 1);
	return (g_glob.ret);
}
