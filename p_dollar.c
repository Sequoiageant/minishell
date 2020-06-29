/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:58:58 by grim              #+#    #+#             */
/*   Updated: 2020/06/29 15:59:04 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		dollar(char *buf, t_state_machine *machine, t_list *env)
{
	int i;
	char *str;

	(void)env;
	i = 0;
	while(buf[i] != ' ' && buf[i])
		i++;
	str = ft_substr(buf, 0, i);
	printf("[%s] -> ENV\n", str);
	// printf("i: %d\n", i);
	if (buf[i] == ' ')
		i++;
	machine->state = LETTER;
	return(i);
}