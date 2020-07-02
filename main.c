/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:14:58 by grim              #+#    #+#             */
/*   Updated: 2020/07/02 11:09:58 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

pid_t	new_pid;

int		ft_handle(char *buf, t_list **env)
{
	t_list	*pipe_list;

	pipe_list = NULL;
	if (ft_parse(buf, *env, &pipe_list) == ERROR)
		return(ERROR);
	ft_traitement(pipe_list, env);
	ft_lstclear(&pipe_list, &del_pipe);
	return (0);
}

void	ctrlc_signal(int signum)
{
	// int new_pid = 0; // prendre le pid du fork, en var globale ?
	if (new_pid)
	{
		ft_putchar_fd('\n', 1);
		printf("pid = %d\n", new_pid);
		kill(new_pid, signum);
		new_pid = 0;
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
	int		ret;
	char	*buf;

	buf = malloc(BUF_SIZE + 1);
	ft_init(&env);
	// ft_print_env(env);
	// int i = 0;
	// while (i < 1)
	while (1)
	{
		if (signal(SIGINT, ctrlc_signal) == SIG_ERR)
			return (1);
		ft_putstr_fd("cmd: ", 1);
		ret = read(1, buf, BUF_SIZE);
		if (!ret)
		{
			ft_putendl_fd("exit", 1);
			exit(0); // remplacer par une fonction d'exit qui free
		}
		buf[ret - 1] = 0; // on a un \n qui s'ajoute à la fin du buffer, dont on ne veut pas
		ft_handle(buf, &env);
		// i++;
	}
	ft_lstclear(&env, &del_key_val);
	free(buf);
	return (0);
}
