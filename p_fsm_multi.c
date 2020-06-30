/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dollar_multi_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:58:58 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 16:20:02 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		fsm_multi(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
    (void)env;
    (void)buf;
    (void)machine;
    if (add_pipe(pipe_list) == FAILURE)
        return (FAILURE);
    printf("[;] -> NEW PIPE \n");
    return (1);
}

int		fsm_pipe(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
    (void)env;
    (void)buf;
    (void)machine;
    if (add_cmd(pipe_list) == FAILURE)
        return (FAILURE);
    printf("[|] -> NEW CMD \n");
    return (1);
}