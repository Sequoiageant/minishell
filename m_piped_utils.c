/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_piped_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:15:15 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 09:19:38 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int     contains_pipe(t_list *cmd_list)
{
    if (cmd_list->next)
        return (TRUE);
    else
        return (FALSE);
}

int		ft_build_pipes(t_list *cmd_list, int ***fd)
{
	int num_cmd;
	int i;

	num_cmd = 0;
	while (cmd_list)
	{
		num_cmd++;
		cmd_list = cmd_list->next;
	}
	*fd = malloc((num_cmd - 1) * sizeof(**fd));
	i = 0;
	while (i < num_cmd - 1)
	{
		(*fd)[i] = malloc(2 * sizeof(int));
		pipe((*fd)[i]);
		i++;
	}
	return (i);
}
