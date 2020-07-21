/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/21 19:14:52 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int ft_join_to_buf(char *added_str, char **initial_str)
{
    char *tmp;
    
    tmp = *initial_str;
	if ((*initial_str = ft_strjoin(tmp, added_str)) == NULL)
		return (FAILURE);
    free(tmp);
    free(added_str);
    #ifdef DEBUG_PARSING
		printf("buf: [%s]\n", *initial_str);
	#endif
    return (SUCCESS);
}


int red_backslash(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)cmd;
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER ", buf[1]);
	#endif
	if (ft_join_to_buf(char_to_str(buf[1]), &cmd->buf) == FAILURE)
		return (FAILURE);
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
		printf("[%c] -> LETTER ", *buf);
	#endif
	if ((ft_join_to_buf(char_to_str(*buf), &cmd->buf) == FAILURE))
		return (FAILURE);
	return (1);
}

int red_redir(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
   (void)m;
   (void)cmd;
	#ifdef DEBUG_PARSING
		printf("[%c] -> REDIR \n", *buf);
	#endif
   return (1);
}