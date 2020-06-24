/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:23:26 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/13 16:19:47 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *p;
	t_list *tmp;

	if (lst == 0 || *lst == 0 || del == 0)
		return ;
	p = *lst;
	while (p)
	{
		(*del)(p->content);
		tmp = p->next;
		free(p);
		p = tmp;
	}
	*lst = 0;
}
