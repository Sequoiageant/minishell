/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipe_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:34:48 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 15:35:31 by grim             ###   ########.fr       */
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
   ft_lstadd_back(pipe_list, ft_lstnew(cmd_list));
   return(0);
}

int     ft_join_to_cmd_buf(char *str, t_list *pipe_list)
{
    t_list  *cmd_list;
    t_cmd   *cmd;
    char    *tmp;
    
    while (pipe_list->next)
        pipe_list = pipe_list->next;
    cmd_list = (t_list*)pipe_list->content;
    while (cmd_list->next)
        cmd_list = cmd_list->next;
    cmd = (t_cmd*)cmd_list->content;
    tmp = cmd->buf;
    cmd->buf = ft_strjoin(tmp, str);
    free(tmp);
    free(str);
    // on ne free pas str --> à gérer au cas par cas (dans le cas du dollar, on ne veut pas free un maillon de la t_list env...)
    printf("buf: [%s]\n", cmd->buf);
    return(1);
}

char    *char_to_str(char c)
{
    char *str;

    str = malloc(2);
    str[0] = c;
    str[1] = 0;
    return (str);
}