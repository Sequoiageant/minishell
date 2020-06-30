/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:58:58 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 18:35:07 by grim             ###   ########.fr       */
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
    if (add_cmd(*pipe_list) == FAILURE)
        return (FAILURE);
    printf("[|] -> NEW CMD \n");
    return (1);
}

// int		fsm_redir(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
// {
//     (void)env;
//     (void)buf;
//     (void)machine;
//     (void)pipe_list;
//     if (*buf == '>')
//     {
//         if (buf[1] == '>')
//         {
//             printf("[>>] -> REDIR \n");
//             // fill_redir_append(pipe_list)
//             return (2);
//         }
//         else
//             printf("[>] -> REDIR \n");
//     }
//     else
//         printf("[<] -> REDIR \n");
//     return (1);
// }