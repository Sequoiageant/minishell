/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:47:19 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/27 13:26:31 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t	ft_strchr_pos(const char *s, int c)
{
	size_t	len;

	printf("str: %s\n", s);

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

int main(int argc, char const *argv[])
{
	size_t	i;
	size_t	len;
	char	*str;

	if (argc == 2)
	{
		i = 0;
		len = 0;
		str = strdup(argv[1]);
		while (str[i])
		{
			len = ft_strchr_pos(str+i, '$');
			printf("len: %ld\n", len);
			i+=(len + 1);
			printf("i: %ld\n", i);
		}
		free(str);
	}
	return (0);
}