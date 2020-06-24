/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:32:36 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/08 18:58:04 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	max;
	unsigned int	slen;
	char			*t;

	if (s == 0)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		max = 0;
	else if (len < (slen - start))
		max = len;
	else
		max = slen - start;
	if (!(t = malloc((max + 1) * sizeof(*t))))
		return (NULL);
	i = 0;
	while (i < max)
	{
		t[i] = s[i + start];
		i++;
	}
	t[i] = 0;
	return (t);
}
