/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_clean_quotes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 12:43:54 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:31:26 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int		cl_backslash(t_fsm_cmd *m, char *buf, char **cleaned)
{
	(void)m;
	if (buf[1])
	{
		ft_join_to_str(char_to_str(buf[1]), cleaned);
		return (2);
	}
	return (1);
}

int		cl_flag_quote(t_fsm_cmd *m, char *buf, char **cleaned)
{
	(void)buf;
	(void)cleaned;
	if (m->flag_quote == ON)
		m->flag_quote = OFF;
	else
		m->flag_quote = ON;
	return (1);
}

int		cl_flag_dquote(t_fsm_cmd *m, char *buf, char **cleaned)
{
	(void)buf;
	(void)cleaned;
	if (m->flag_dquote == ON)
		m->flag_dquote = OFF;
	else
		m->flag_dquote = ON;
	return (1);
}

int		cl_letter(t_fsm_cmd *m, char *buf, char **cleaned)
{
	(void)m;
	ft_join_to_str(char_to_str(buf[0]), cleaned);
	return (1);
}
