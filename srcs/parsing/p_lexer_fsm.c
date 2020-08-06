/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer_fsm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:29:34 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int			lex_backslash(t_fsm_lexer *m, char *buf, int i)
{
	(void)m;
	if (buf[i + 1])
		return (2);
	else
		return (1);
}

int			lex_flag(t_fsm_lexer *m, char *buf, int i)
{
	if (buf[i] == '"')
	{
		if (m->flag_dquote == ON)
			m->flag_dquote = OFF;
		else
			m->flag_dquote = ON;
	}
	else
	{
		if (m->flag_quote == ON)
			m->flag_quote = OFF;
		else
			m->flag_quote = ON;
	}
	return (1);
}

int			lex_letter(t_fsm_lexer *m, char *buf, int i)
{
	(void)m;
	(void)buf;
	(void)i;
	return (1);
}
