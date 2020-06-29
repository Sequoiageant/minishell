/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/06/29 15:58:00 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		backslash(char *buf, t_state_machine *machine, t_list *env)
{
	(void)machine;
	(void)env;
	printf("[%c] -> LETTER (ESCAPED)\n", buf[1]);
	return(2);
}

int		flag(char *buf, t_state_machine *machine, t_list *env)
{
	(void)env;
	if (*buf == '"')
	{
		if (machine->flag_dquote)
			machine->flag_dquote = 0;
		else
			machine->flag_dquote = 1;
	}
	else
	{
		if (machine->flag_quote)
			machine->flag_quote = 0;
		else
			machine->flag_quote = 1;
	}
	return (1);
}

int		letter(char *buf, t_state_machine *machine, t_list *env)
{
	(void)machine;
	(void)env;
	printf("[%c] -> LETTER\n", *buf);
	return (1);
}