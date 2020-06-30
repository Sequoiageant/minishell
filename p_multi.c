/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_multi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:55:25 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 10:38:04 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		multi(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
    (void)env;
    (void)buf;
    (void)machine;
    add_pipe(pipe_list);
	while ((*pipe_list)->next)
		*pipe_list = (*pipe_list)->next;
	printf("[;] -> NEW PIPE ");
    return (1);
}