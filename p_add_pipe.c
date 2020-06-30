/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_add_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:34:48 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 16:28:47 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"


int     init_cmd_list(t_list **cmd_list)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof *cmd);
    cmd->buf = malloc(1);
    cmd->buf[0] = 0;
    ft_lstadd_back(cmd_list, ft_lstnew(cmd));
    return (0);
}

int		add_pipe(t_list **pipe_list)
{
    
   t_list *cmd_list;
   
   cmd_list = NULL;
   init_cmd_list(&cmd_list);
   cmd_list->next = NULL;
   ft_lstadd_back(pipe_list, ft_lstnew(cmd_list));
   return(0);
}
