/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/30 12:11:46 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int	is_valid_identifier(char *str)
{
	if ((!ft_isalpha(str[0]) && str[0] != '_') || !ft_isalnum_str(str))
		return (FALSE);
	return (TRUE);
}

int	ms_env(int argc, char **av, t_list **env)
{
	(void)argc;
	(void)av;
	ft_print_env(*env);
	return (SUCCESS);
}

int	ms_unset(int argc, char **av, t_list **env)
{
	size_t	i;
	int		ret;

	ret = SUCCESS;
	if (argc > 1)
	{
		{
			i = 1;
			while (av[i])
			{
				if (is_valid_identifier(av[i]))
					lst_delone_env(env, av[i]);
				else
				{
					put_err("unset: `", av[i], "': not a valid identifier", 1);
					ret = FAILURE;
				}
				i++;
			}
		}
	}
	return (ret);
}
