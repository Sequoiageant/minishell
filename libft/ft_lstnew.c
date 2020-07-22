/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:26:49 by bbrunet           #+#    #+#             */
/*   Updated: 2020/07/22 15:29:50 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	if (!(l = malloc(sizeof(*l))))
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}
