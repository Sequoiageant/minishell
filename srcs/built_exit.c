/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/15 19:24:33 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

void			ms_exit(t_list *pipe_list, int ac, char **argv, t_list **env)
{
	int	ret;

	ret = 0;
	ft_putendl_fd("exit", 1);
	if (ac > 2)
	{
		// printf("%s\n", argv[2]);
		put_err("exit: ", NULL, "too many arguments");
	}
	else if (ac == 2)
	{
		if (is_int(argv[1], '-'))
			ret = ft_atoi(argv[1]);
		else
		{
			put_err("exit: ", argv[1], ": numeric argument required");
			ret = 2;
		}
		ft_free_all(pipe_list, env);
		exit(ret);
	}
	else
	{
		ft_free_all(pipe_list, env);
		exit(ret);
	}
}
