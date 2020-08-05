/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_clean_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 12:43:54 by grim              #+#    #+#             */
/*   Updated: 2020/08/03 14:15:28 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		cl_backslash(t_fsm_cmd *m, char *buf, char **cleaned)
{
	(void)m;
    #ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER \n", buf[1]);
	#endif
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
	#ifdef DEBUG_PARSING
		printf("['] ");
	#endif
	if (m->flag_quote == ON)
	{	
		m->flag_quote = OFF;
		#ifdef DEBUG_PARSING
			printf("-> QUOTE OFF\n");
		#endif
	}
	else
	{
		m->flag_quote = ON;
		#ifdef DEBUG_PARSING
			printf("-> QUOTE ON\n");
		#endif
	}
	return (1);
}

int		cl_flag_dquote(t_fsm_cmd *m, char *buf, char **cleaned)
{
	(void)buf;
    (void)cleaned;
    #ifdef DEBUG_PARSING
		printf("[\"] ");
	#endif
	if (m->flag_dquote == ON)
	{
		m->flag_dquote = OFF;
		#ifdef DEBUG_PARSING
			printf("-> DQUOTE OFF\n");
		#endif
	}
	else
	{
		m->flag_dquote = ON;
		#ifdef DEBUG_PARSING
			printf("-> DQUOTE ON\n");
		#endif
	}
	return (1);
}

int		cl_letter(t_fsm_cmd *m, char *buf, char **cleaned)
{
	(void)m;
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER \n", *buf);
	#endif
    ft_join_to_str(char_to_str(buf[0]), cleaned);
	return (1);
}