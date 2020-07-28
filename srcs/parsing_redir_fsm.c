/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/28 15:01:07 by grim             ###   ########.fr       */
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
	(void)cmd;
	if (buf[1] == '\'' && buf[2] == ' ') // cas particulier d'un '' en début de commande
	{
		ft_lstadd_back(&cmd->argv_list, ft_lstnew(ft_strdup(""))); 
		#ifdef DEBUG_PARSING
			printf("[''] -->NEW ARGV \n");
		#endif
	}
	if (m->flag_quote)
		m->flag_quote = 0;
	else
		m->flag_quote = 1;
	return (1);
}

int red_flag_dquote(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)cmd;
	if (buf[1] == '"' && buf[2] == ' ') // cas particulier d'un "" en début de commande
	{
		ft_lstadd_back(&cmd->argv_list, ft_lstnew(ft_strdup(""))); 
		#ifdef DEBUG_PARSING
			printf("[""] -->NEW ARGV \n");
		#endif
	}
	if (m->flag_dquote)
		m->flag_dquote = 0;
	else
		m->flag_dquote = 1;
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
