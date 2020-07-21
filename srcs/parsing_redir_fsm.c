/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/21 17:20:21 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int red_backslash(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)cmd;
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER \n", buf[1]);
	#endif

	// if (ft_join_to_cmd_buf(char_to_str(buf[1]), *p_list) == FAILURE)
	// 	return (FAILURE);
	return (2);
}

int red_flag(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)cmd;
    if (*buf == '"')
	{
		if (m->flag_dquote)
			m->flag_dquote = 0;
		else
			m->flag_dquote = 1;
	}
	else
	{
		if (m->flag_quote)
			m->flag_quote = 0;
		else
			m->flag_quote = 1;
	}
	return (1);
}

int red_letter(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)cmd;
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER \n", *buf);
	#endif
	// if ((ft_join_to_cmd_buf(char_to_str(*buf), *p_list) == FAILURE))
	// 	return (FAILURE);
	return (1);
}

int red_redir(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
   (void)m;
   (void)buf;
   (void)cmd;
   return (1);
}