/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:29:23 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:30:03 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int	backslash_activated(char *buf, t_fsm_lexer *machine, int i)
{
	if (machine->flag_quote)
		return (0);
	if (machine->flag_dquote)
	{
		if (buf[i + 1] == '$' || buf[i + 1] == '"' || buf[i + 1] == '\\')
			return (TRUE);
		else
			return (FALSE);
	}
	return (1);
}

static void	chose_state(char *buf, t_fsm_lexer *machine, int i)
{
	if (buf[i] == '"' && !machine->flag_quote)
		machine->state = L_FLAG;
	else if (buf[i] == '\'' && !machine->flag_dquote)
		machine->state = L_FLAG;
	else if (buf[i] == '\\' && backslash_activated(buf, machine, i))
		machine->state = L_BACKSLASH;
	else if ((buf[i] == ';' || buf[i] == '|')
	&& !machine->flag_quote && !machine->flag_dquote)
		machine->state = L_CHECK_AVANT;
	else if ((buf[i] == '>' || buf[i] == '<')
	&& !machine->flag_quote && !machine->flag_dquote)
		machine->state = L_CHECK_APRES;
	else
		machine->state = L_LETTER;
}

int			lexer(char *buf)
{
	t_fsm_lexer			machine;
	static t_func_lex	func[NB_LEXER] = {lex_letter,
	lex_backslash, lex_flag, lex_check_apres, lex_check_avant};
	int					ret;
	int					i;

	i = 0;
	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	while (buf[i])
	{
		chose_state(buf, &machine, i);
		ret = func[machine.state](&machine, buf, i);
		if (ret == FAILURE)
			return (FAILURE);
		i += ret;
	}
	return (SUCCESS);
}
