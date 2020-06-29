/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_flag_backslash_letter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/06/29 19:15:31 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		backslash(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	(void)machine;
	(void)env;
	(void)pipe_list;
	ft_join_str_to_pipe(char_to_str(buf[1]), *pipe_list);
	printf("[%c] -> LETTER (ESCAPED)\n", buf[1]);
	return(2);
}

int		flag(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	(void)env;
	(void)pipe_list;
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

int		letter(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	(void)machine;
	(void)env;
	ft_join_str_to_pipe(char_to_str(*buf), *pipe_list);
	printf("[%c] -> LETTER\n", *buf);
	return (1);
}