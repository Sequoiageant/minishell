/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_buf2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:58:58 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 10:23:08 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int		fsm_multi(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)env;
	(void)buf;
	(void)m;
	ft_lstadd_back(p_list, ft_lstnew(NULL));
	if (add_cmd(*p_list) == FAILURE)
		return (FAILURE);
	return (1);
}

int		fsm_pipe(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)env;
	(void)buf;
	(void)m;
	if (add_cmd(*p_list) == FAILURE)
		return (FAILURE);
	return (1);
}

int		fsm_backsl(char *buf, t_state_machine *m, t_list *e, t_list **p_list)
{
	(void)m;
	(void)e;
	if (ft_join_to_cmd_buf(char_to_str(buf[0]), *p_list) == FAILURE)
		return (FAILURE);
	if (buf[1] && ft_join_to_cmd_buf(char_to_str(buf[1]), *p_list) == FAILURE)
		return (FAILURE);
	if (buf[1])
		return (2);
	else
		return (1);
}

int		fsm_flag(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)env;
	(void)p_list;
	if (*buf == '"')
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
	if (ft_join_to_cmd_buf(char_to_str(buf[0]), *p_list) == FAILURE)
		return (FAILURE);
	return (1);
}

int		fsm_letter(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)m;
	(void)env;
	if ((ft_join_to_cmd_buf(char_to_str(*buf), *p_list) == FAILURE))
		return (FAILURE);
	return (1);
}
