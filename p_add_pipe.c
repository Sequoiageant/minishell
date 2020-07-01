/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_add_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:34:48 by grim              #+#    #+#             */
/*   Updated: 2020/07/01 17:22:17 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		add_pipe(t_list **pipe_list)
{
    
   t_list *cmd_list;
   t_cmd *cmd;
   
   cmd = malloc(sizeof *cmd);
   ft_init_cmd(cmd);
   cmd_list = ft_lstnew(cmd);
   ft_lstadd_back(pipe_list, ft_lstnew(cmd_list));
   return(0);
}
