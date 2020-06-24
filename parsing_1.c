/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:35:31 by grim              #+#    #+#             */
/*   Updated: 2020/06/24 15:42:51 by grim             ###   ########.fr       */
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

int ft_fill_cmd(t_list *cmd_list, char *buf)
{
	// c'est ici qu'on parse de nouveau buf pour detecter les >, >>, | et set les flags
	// ensuite on set les char **argv et int argc
	
	// cas où on a pas de flag et une seule commande
	t_cmd *cmd;
	
	cmd = (t_cmd*)cmd_list->content;
	cmd->argv = ft_split(buf, ' ');
	cmd->argc = ft_count_args(cmd->argv);
    return (0);
}