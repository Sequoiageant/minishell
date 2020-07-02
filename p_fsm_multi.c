/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:58:58 by grim              #+#    #+#             */
/*   Updated: 2020/07/02 16:43:41 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		fsm_multi(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
    (void)env;
    (void)buf;
    (void)machine;
	#ifdef DEBUG_PARSING
        printf("[;] -> NEW PIPE \n");
	#endif
    if (add_pipe(pipe_list) == FAILURE)
        return (FAILURE);
    if (add_cmd(*pipe_list) == FAILURE)
        return (FAILURE);
    return (1);
}

int		fsm_pipe(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
    (void)env;
    (void)buf;
    (void)machine;
	#ifdef DEBUG_PARSING
        printf("[|] -> NEW CMD \n");
	#endif
    if (add_cmd(*pipe_list) == FAILURE)
        return (FAILURE);
    return (1);
}
