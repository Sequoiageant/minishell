/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:48:14 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/01 15:55:08 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "libft.h"
#include "mshell.h"

pid_t	new_pid;

int		ft_fork2(char **cmd)
{
	int		status;
	char	*filepath;

	filepath = ft_calloc(100, 1);
	new_pid = fork();
	if (new_pid == 0)
	{
		// new process
		ft_putstr_fd(">>Inside new process\n", 1);
		// va chercher ./cmd[0] pour l'executer
		// il faudrait au préalable chercher dans PATH pour trouver l'executable correspondant à la commande. Puis donner le "chemin" de cet executable en input (à la place de cmd[0])
		ft_strlcat(filepath, "executables/", 100);
		ft_strlcat(filepath, cmd[1], 100);
		printf("filename: %s\n", filepath);
		if (execve(filepath, cmd, NULL) == -1)
			printf(">>Exec failed\n");
		// else should not return
	}
	else
	{
		// old process
		wait(&status);
		// return (new_pid);
	}
	free(filepath);
	return (0);
}

void	ctrlc_signal(int signum)
{
	if (new_pid)
	{
		printf("%d\n", new_pid);
		kill(new_pid, SIGINT);
		// ft_putchar_fd('\n', 1);
		// ft_putstr_fd("cmd: ", 1);
	}
	else
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("new cmd: ", 1);
	}
}
void	ctrld_signal(int signum)
{
	if (signum)
	{
		ft_putchar_fd('\n', 1);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("cmd: ", 1);
	}
}

int main(int ac, char **av)
{
	int		ret;
	char	*buf;

	// if (signal(SIGQUIT, ctrld_signal) == SIG_ERR)
	// 	return (1);
		ft_putstr_fd("cmd: ", 1);
		ft_fork2(av);
	while (1)
	{
		if (signal(SIGINT, ctrlc_signal) == SIG_ERR)
			return (1);
		ret = read(1, buf, BUF_SIZE);
		printf("ret: %d\n", ret);
		if (ret == -1)
			exit(0);
		// buf[ret - 1] = 0; // on a un \n qui s'ajoute à la fin du buffer, dont on ne veut pas
		// ft_handle(buf, &env);
		// i++;
	}
	return (0);
}*/