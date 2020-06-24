/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:49:28 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/13 18:29:40 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*tmp;
	size_t	i;

	if (!(ptr = malloc(count * size)))
		return (NULL);
	tmp = ptr;
	i = 0;
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (ptr);
}
