/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/29 09:56:56 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int red_backslash(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)cmd;
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER ", buf[1]);
	#endif
	if (buf[1] == 0) // cas ou on a un / en fin de commande
		return (1);
	if (m->flag_redir)
	{
		ft_join_to_redir(char_to_str(buf[1]), cmd->redir);
		if (buf[1] == '$')
			ft_set_env_flag(cmd, FALSE, REDIR);
	}
	else
	{
		ft_join_to_argv(char_to_str(buf[1]), cmd);
		if (buf[1] == '$')
			ft_set_env_flag(cmd, FALSE, ARGV);
	}
	return (2);
}

int red_flag_quote(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	if (buf[1] == '\'')
	{
		#ifdef DEBUG_PARSING
			printf("[\"\"] ");
		#endif
		ft_join_to_argv(ft_strdup(""), cmd);
		return(2);
	}
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

int red_flag_dquote(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	if (buf[1] == '"')
	{
		#ifdef DEBUG_PARSING
			printf("[\"\"] ");
		#endif
		ft_join_to_argv(ft_strdup(""), cmd);
		return(2);
	}
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

int red_letter(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)m;
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER ", *buf);
	#endif
	if (m->flag_redir)
	{
		ft_join_to_redir(char_to_str(buf[0]), cmd->redir);
		if (buf[0] == '$')
			ft_set_env_flag(cmd, FALSE, REDIR);
	}
	else
	{
		ft_join_to_argv(char_to_str(buf[0]), cmd);
		if (buf[0] == '$')
			ft_set_env_flag(cmd, FALSE, ARGV);
	}
	return (1);
}
