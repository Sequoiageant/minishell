/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:34:48 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 09:19:13 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		add_pipe(t_list **pipe_list)
{
	t_pipeline *pipe;
	// char *pipe_buf;
	
	pipe = malloc(sizeof(*pipe)); 
	pipe->cmd_list = NULL;
	pipe->pipe_buf = malloc(1);
	pipe->pipe_buf[0] = 0;
	ft_lstadd_back(pipe_list, ft_lstnew(pipe));
	return(0);
}

int ft_join_str_to_pipe(char *str, t_list *pipe_list)
{
    t_pipeline *pipe;
    char *tmp;
    
    while (pipe_list->next)
        pipe_list = pipe_list->next;
    pipe = (t_pipeline*)pipe_list->content;
    tmp = pipe->pipe_buf;
    pipe->pipe_buf = ft_strjoin(tmp, str);
    free(tmp); // on ne free pas str car c'est un maillon de la t_list env
    return(1);
}

char *char_to_str(char c)
{
    char *str;

    str = malloc(2);
    str[0] = c;
    str[1] = 0;
    return (str);
}