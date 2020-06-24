/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:21:29 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/13 12:04:03 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_mem_reverse_cpy(void *dst, const void *src, size_t n)
{
	int			i;
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	i = n - 1;
	while (i >= 0)
	{
		*(d + i) = *(s + i);
		i--;
	}
	return (dst);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (dst == 0 && src == 0)
		return (dst);
	d = dst;
	s = src;
	i = 0;
	while (i < len)
	{
		if (d == s + i)
			return (ft_mem_reverse_cpy(dst, src, len));
		else
			i++;
	}
	return (ft_memcpy(dst, src, len));
}
