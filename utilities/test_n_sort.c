/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_n_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:23:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/13 10:48:40 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

// clang -Wall -Wextra -Werror test_n_sort.c -L../libft/ -lft -I../libft/

void	display_tab2(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
}
void	free_tab2(char **tab)
{
	int i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

size_t	ft_strnlen(char *str, char stop)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == stop)
			return (len);
		len++;
	}
	return (len);
}

void	ft_n_sort_string_tab(char **tab, char stop)
{
	size_t	i;
	size_t	len;
	char	*temp;

	i = 0;
	while (tab[i + 1])
	{
		len = ft_strnlen(tab[i], stop);
		if (ft_strncmp(tab[i], tab[i + 1], len) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

int	main(void)
{
	char	**tab;
	int		i;;
	char	*env[5] = {
		"julien=a",
		"basile=a",
		"julie=a",
		"roger=a",
		"albert=a",
	};
	tab = malloc(6 * sizeof(char *));
	tab[5] = NULL;
	i = 0;
	while (i < 5)
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	ft_n_sort_string_tab(tab, '=');
	display_tab2(tab);
	free_tab2(tab);
	return (0);
}