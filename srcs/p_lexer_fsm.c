/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer_fsm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/07/30 12:28:21 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int			lex_backslash(t_fsm_lexer *m, char *buf, int i)
{
	(void)m;
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER\n ", buf[1]);
	#endif
	
	if (buf[i + 1])
		return (2);
	else
		return (1); // si on a un backslash en fin de commande, pour ne pas causer de "invalid read"
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
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER\n", buf[i]);
	#endif
	return (1);
}
