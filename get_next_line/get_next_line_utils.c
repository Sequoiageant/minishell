/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:52:50 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 15:10:11 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static	void	*ft_memcpy(char *dst, const char *src, size_t n)
{
	size_t i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char			*ft_strdup(const char *src)
{
	char	*dest;
	size_t	len;

	dest = NULL;
	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest != NULL)
		ft_memcpy(dest, src, len + 1);
	return (dest);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		dst = ft_strdup(s2);
	else if (!s2)
		dst = ft_strdup(s1);
	else
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		if (!(dst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
			return (NULL);
		ft_memcpy(dst, s1, len_s1);
		ft_memcpy(dst + len_s1, s2, len_s2 + 1);
	}
	return (dst);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	dst = NULL;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL || dst == NULL)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		dst[0] = '\0';
	else
	{
		dst = ft_memcpy(dst, s + start, len);
		dst[len] = '\0';
	}
	return (dst);
}
