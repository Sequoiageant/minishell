/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:31:15 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/13 12:06:23 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_debut(const char *s1, const char *set)
{
	int debut;

	debut = 0;
	while (ft_isset(s1[debut], set) && s1[debut])
		debut++;
	return (debut);
}

static int	ft_fin(const char *s1, const char *set)
{
	int fin;

	fin = ft_strlen(s1) - 1;
	while (ft_isset(s1[fin], set) && fin > 0)
		fin--;
	return (fin);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	char	*p;
	int		debut;
	int		fin;
	int		i;

	if (s1 == 0 || set == 0)
		return (NULL);
	debut = ft_debut(s1, set);
	fin = ft_fin(s1, set);
	if (fin < debut)
		debut = fin + 1;
	if (!(p = malloc((fin - debut + 2) * sizeof(*p))))
		return (NULL);
	i = 0;
	while (i < fin - debut + 1)
	{
		p[i] = s1[debut + i];
		i++;
	}
	p[i] = 0;
	return (p);
}
