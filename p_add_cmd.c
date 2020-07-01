/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_add_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:09:36 by grim              #+#    #+#             */
/*   Updated: 2020/07/01 17:03:47 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void     ft_init_cmd(t_cmd *cmd)
{
    cmd->input_file = 0;
    cmd->output_file = 0;
    cmd->output_file_append = 0;
    cmd->file = NULL;
    cmd->argv = NULL;
    cmd->argc = 0;
    cmd->buf = malloc(1);
    cmd->buf[0] = 0;
}


int     add_cmd(t_list *pipe_list) // ne marche que sur une cmd_list déja existante
{
    t_list  *cmd_list;
    t_cmd   *cmd;
    
    while (pipe_list->next)
        pipe_list = pipe_list->next;
    cmd_list = (t_list*)pipe_list->content;
    cmd = malloc(sizeof *cmd);
    ft_init_cmd(cmd);
    ft_lstadd_back(&cmd_list, ft_lstnew(cmd)); 
    
    return (0);
}