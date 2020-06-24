/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:40:50 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/13 11:31:08 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *t;
	t_list *init;

	if (lst == 0 || f == 0)
		return (NULL);
	t = ft_lstnew((*f)(lst->content));
	if (t == 0)
		return (NULL);
	init = t;
	while (lst->next)
	{
		t->next = ft_lstnew((*f)(lst->next->content));
		if (t->next == 0)
		{
			ft_lstclear(&init, del);
			return (NULL);
		}
		lst = lst->next;
		t = t->next;
	}
	printf("Hello\n");
	return (init);
}
