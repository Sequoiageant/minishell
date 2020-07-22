/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/22 15:35:31 by julnolle         ###   ########.fr       */
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

int	ms_env(int argc, char *argv[], t_list **env)
{
	(void)argc;
	(void)argv;
	ft_print_env(*env);
	return (SUCCESS);
}

int	ms_unset(int argc, char *argv[], t_list **env)
{
	size_t	i;

	if (argc > 1)
	{
		{
			i = 1;
			while (argv[i])
			{
				if (is_valid_identifier(argv[i]))
					lst_delone_env(env, argv[i]);
				else
				{
					put_err("unset: `", argv[i], "': not a valid identifier", TRUE);
					return (FAILURE);
				}
				i++;
			}
		}
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
