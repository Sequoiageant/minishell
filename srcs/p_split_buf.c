/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:58:58 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 09:30:43 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		fsm_multi(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)env;
	(void)buf;
	(void)m;
	#ifdef DEBUG_PARSING
		printf("[;] -> NEW PIPE \n");
	#endif
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
	#ifdef DEBUG_PARSING
		printf("[|] -> NEW CMD \n");
	#endif
	if (add_cmd(*p_list) == FAILURE)
		return (FAILURE);
	return (1);
}

int		fsm_backslash(char *buf, t_state_machine *m, t_list *e, t_list **p_list)
{
	(void)m;
	(void)e;
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER ", buf[1]);
	#endif
	
	if (ft_join_to_cmd_buf(char_to_str(buf[0]), *p_list) == FAILURE)
		return (FAILURE);
	if (buf[1] && ft_join_to_cmd_buf(char_to_str(buf[1]), *p_list) == FAILURE)
		return (FAILURE);
	if (buf[1])
		return (2);
	else
		return (1); // si on a un backslash en fin de commande, pour ne pas causer de "invalid read"
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

int			fsm_letter(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)m;
	(void)env;
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER ", *buf);
	#endif
	if ((ft_join_to_cmd_buf(char_to_str(*buf), *p_list) == FAILURE))
		return (FAILURE);
	return (1);
}

