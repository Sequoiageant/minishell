/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 09:51:18 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/12 18:32:22 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t j;
	size_t ldest;
	size_t lsrc;

	ldest = ft_strlen((const char *)dest);
	lsrc = ft_strlen(src);
	if (ldest >= dstsize)
		return (dstsize + lsrc);
	j = 0;
	while (j < lsrc && j < dstsize - 1 - ldest)
	{
		dest[ldest + j] = src[j];
		j++;
	}
	dest[ldest + j] = 0;
	return (ldest + lsrc);
}
