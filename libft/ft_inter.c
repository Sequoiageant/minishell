/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:41:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/24 12:33:28 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cutstr(char *a, int index)
{
	int		i;
	char	tmp;

	i = index;
	while (a[i + 1])
	{
		tmp = a[i + 1];
		a[i] = tmp;
		i++;
	}
	a[i] = 0;
}

char	*ft_inter(char *a, char *b)
{
	int i;

	if (a == NULL || b == NULL)
		return (NULL);
	i = 0;
	while (a[i])
	{
		if (!ft_strchr(b, a[i]))
		{
			ft_cutstr(a, i);
			i = 0;
		}
		else
		{
			i++;
		}
	}
	return (a);
}
