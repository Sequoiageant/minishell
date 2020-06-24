/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:35:31 by grim              #+#    #+#             */
/*   Updated: 2020/06/24 16:37:48 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int ft_count_args(char **argv)
{
    int i;
    
    i = 0;
    while (argv[i])
        i++;
    return(i);
}

int ft_fill_cmd_args(t_list *cmd_list, char *buf)
{
	t_cmd *cmd;

    while (cmd_list)
    {
        cmd = (t_cmd*)cmd_list->content;
        cmd->argv = ft_split(buf, ' ');
        cmd->argc = ft_count_args(cmd->argv);
        cmd_list = cmd_list->next;    
    }
    return (0);
}

int ft_fill_cmd(t_list *cmd_list, char *buf)
{
//  ft_fill_cmd_flags A FAIRE
//  ft_fill_cdm_buffer A FAIRE --> ajouter char *buf à la structure t_cmd ?
	ft_fill_cmd_args(cmd_list, buf);
    return (0);
}