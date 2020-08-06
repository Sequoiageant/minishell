/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/06 09:26:01 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static	int		is_int(char *str, char sign)
{
	int	i;

	i = 0;
	if (sign == '+')
	{
		if (str[0] == '+')
			i++;
	}
	else if (sign == '-')
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static	void	ft_free_all(t_list *pipe_list, t_list **env)
{
	ft_lstclear(env, &del_key_val);
	ft_lstclear(&pipe_list, &del_pipe);
}

static	int		ft_exit_error1(char *arg)
{
	int	ret;

	ret = 1;
	if (is_int(arg, '-'))
		put_err("exit: ", NULL, "too many arguments", TRUE);
	else
	{
		put_err("exit: ", arg, ": numeric argument required", TRUE);
		ret = 2;
	}
	return (ret);
}

static	int		ft_exit_error2(char *arg)
{
	int	ret;

	ret = 0;
	if (is_int(arg, '-'))
		ret = ft_atoi(arg);
	else
	{
		put_err("exit: ", arg, ": numeric argument required", TRUE);
		ret = 2;
	}
	return (ret);
}

void			ms_exit(t_list *pipe_list, int ac, char **argv, t_list **env)
{
	if (pipe_list)
		ft_putendl_fd("exit", 1);
	if (ac > 2)
	{
		g_glob.ret = ft_exit_error1(argv[1]);
		if (g_glob.ret == 2)
			exit(g_glob.ret);
		if (!pipe_list)
			exit(g_glob.ret);
	}
	else if (ac == 2)
	{
		g_glob.ret = ft_exit_error2(argv[1]);
		ft_free_all(pipe_list, env);
		exit(g_glob.ret);
	}
	else
	{
		ft_free_all(pipe_list, env);
		exit(g_glob.ret);
	}
}
