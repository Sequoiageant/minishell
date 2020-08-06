/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_buf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:37:07 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 10:23:06 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int	backslash_activated(char *buf, t_state_machine *machine)
{
	if (machine->flag_quote)
		return (0);
	if (machine->flag_dquote)
	{
		if (buf[1] == '$' || buf[1] == '"' || buf[1] == '\\')
			return (TRUE);
		else
			return (FALSE);
	}
	return (1);
}

static void	chose_state(char *buf, t_state_machine *machine)
{
	if (*buf == '"' && !machine->flag_quote)
		machine->state = FLAG;
	else if (*buf == '\'' && !machine->flag_dquote)
		machine->state = FLAG;
	else if (*buf == '\\' && backslash_activated(buf, machine))
		machine->state = BACKSLASH;
	else if (*buf == ';' && !machine->flag_quote && !machine->flag_dquote)
		machine->state = MULTI;
	else if (*buf == '|' && !machine->flag_quote && !machine->flag_dquote)
		machine->state = PIPE;
	else
		machine->state = LETTER;
}

int			parser_split_buf(char *buf, t_list *env, t_list **pipe_list)
{
	t_state_machine		machine;
	static t_function	func[NB_SPLIT_BUF] = {fsm_letter,
	fsm_backsl, fsm_flag, fsm_multi, fsm_pipe};
	int					ret;

	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	while (*buf != '\0')
	{
		chose_state(buf, &machine);
		ret = func[machine.state](buf, &machine, env, pipe_list);
		if (ret == FAILURE)
			return (FAILURE);
		buf += ret;
	}
	return (SUCCESS);
}
