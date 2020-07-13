/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/13 17:57:16 by julnolle         ###   ########.fr       */
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

static	int		manage_ret(int ret)
{
	if (ret < 0)
		ret = 256 + ret;
	else if (ret > 256)
		ret = ret - 256;
	return (ret);
}

static	void	ft_free_all(t_list *cmd_list, t_list **env)
{
	ft_lstclear(&cmd_list, &del_cmd);
	ft_lstclear(env, &del_key_val);
}

void			ms_exit(t_list *cmd_list, char **argv, t_list **env)
{
	int	ret;

	ret = 0;
	ft_putendl_fd("exit", 1);
	if (argv[1] && argv[2])
	{
		printf("%s\n", argv[2]);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (argv[1])
	{
		if (is_int(argv[1], '-'))
			ret = manage_ret(ft_atoi(argv[1]));
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			ret = 2;
		}
		ft_free_all(cmd_list, env);
		exit(ret);
	}
	else
	{
		ft_free_all(cmd_list, env);
		exit(ret);
	}
}
