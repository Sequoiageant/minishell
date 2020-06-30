/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_add_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:09:36 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 16:34:23 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int     add_cmd(t_list *pipe_list)
{
    t_list  *cmd_list;
    t_cmd   *cmd;
    
    while (pipe_list->next)
        pipe_list = pipe_list->next;
    cmd_list = (t_list*)pipe_list->content;
    cmd = malloc(sizeof *cmd);
    cmd->buf = malloc(1);
    cmd->buf[0] = 0;
    ft_lstadd_back(&cmd_list, ft_lstnew(cmd)); 
    
    return (0);
}