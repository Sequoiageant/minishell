/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_delchar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:41:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/03 12:29:44 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

char	*ft_str_del_1_sur_2(char *a)
{
	int i;
	int p;

	if (a == NULL)
		return (NULL);
	i = 0;
	p = 1;
	while (a[i])
	{
		if ((i % 2 == p))
		{
			ft_cutstr(a, i);
			if (p == 1)
				p = 0;
			else
				p = 1;
		}
		else
		{
			i++;
		}
	}
	return (a);
}
