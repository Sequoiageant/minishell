/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_filler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 10:09:13 by grim              #+#    #+#             */
/*   Updated: 2020/07/01 14:40:23 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"


int     fill_cmd(t_cmd *cmd)
{
// A character that, when unquoted, separates words. One of the following:
// | & ; ( ) < > space tab
    // int i;
    
    if (contains_redir(cmd->buf))
        fill_redir(cmd);
    if (fill_argv(cmd) == FAILURE)
        return (FAILURE);
    return (1);
    

}

int     fill_pipe(t_list *pipe_list)
{
    t_list *cmd_list;
    t_cmd *cmd;

    cmd_list = (t_list*)pipe_list->content;
    while (cmd_list)
    {
        cmd = (t_cmd*)cmd_list->content;
        if (fill_cmd(cmd) == FAILURE)
            return (FAILURE);
        cmd_list = cmd_list->next;
    }
    return (SUCCESS);
}

int     filler(t_list *pipe_list)
{
    while (pipe_list)
    {
        if (fill_pipe(pipe_list) == FAILURE)
            return (FAILURE);
        printf("PIPE >> \n");
        // print_pipe_bufs(pipe_list);
        // print_pipe_redirs(pipe_list);
        print_pipe_argvs(pipe_list);
        pipe_list = pipe_list->next;
    }
    return(SUCCESS);
    
}