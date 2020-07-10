/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_environ2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:29:53 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/09 17:26:58 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	int i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

int main(int argc, char **argv, char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
