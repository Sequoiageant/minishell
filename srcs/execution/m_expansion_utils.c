/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_expansion_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:04:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/06 11:11:52 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	ft_realloc(char **new, char **src)
{
	if (new == NULL || src == NULL)
		return ;
	if (*src)
	{
		free(*src);
		*src = NULL;
		*src = *new;
	}
}

size_t	ft_strclen(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

size_t	tab2_size(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	free_tab2(tab);
	return (i);
}

void	ft_tab_to_list(t_list **list, char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(tab[i])));
		i++;
	}
	free_tab2(tab);
}

int		is_even(int nb)
{
	return ((nb % 2) == 0);
}
