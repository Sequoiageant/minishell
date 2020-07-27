/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/27 11:16:35 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int red_flag_redir(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	int		offset;
	t_redir	*redir;
	
	// init le t_redir suivant de la chaine et set l'int en fonction du signe < > ou >>
	redir = malloc(sizeof(t_redir));
	redir->file = ft_strdup(""); // pour permettre les str_join
	offset = set_redir_state(buf, &redir->state);
	#ifdef DEBUG_PARSING
		if (redir->state == REDIR_OUT)
			printf("--REDIR > ACTIVATED \n");
		if (redir->state == REDIR_APPEND)
			printf("--REDIR >> ACTIVATED \n");
		if (redir->state == REDIR_IN)
			printf("--REDIR < ACTIVATED \n");
	#endif
	m->flag_redir = 1;
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
	return (offset);
}

int red_backslash(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)cmd;
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER ", buf[1]);
	#endif
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

int red_whitespace(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	int ret;
	
	(void)m;
	(void)cmd;
	ret = 0;
	while (buf[ret] == 9 || buf[ret] == 32)
	{
		ret++;
	}
	if (buf[ret] != 0) // on ajoute un arg sauf: si ce sont des whitespaces à la fin de la commande
	{
		ft_lstadd_back(&cmd->argv_list, ft_lstnew(NULL)); 
		#ifdef DEBUG_PARSING
			printf("--NEW ARGV \n");
		#endif
	}
	return (ret);
}

int red_letter(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	(void)m;
	// on desactive le flag redir lorsqu'on rencontre un espace ou un tab non "escapés"
	// on ajoute un argv lorsqu'on rencontre un espace ou un tab non "escapé"
	if (!m->flag_quote && !m->flag_dquote && (*buf == 9 || *buf == 32))
	{
		if (m->flag_redir)
		{
			m->flag_redir = 0;
			#ifdef DEBUG_PARSING
				printf("--REDIR OFF \n");
			#endif
		}
	}	
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

int 		red_dollar(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	int		i;
	char	*str;

	(void)m;
	i = count_dollar_char(buf);
	str = ft_substr(buf, 0, i + 1); // +1 car on compte le $
	#ifdef DEBUG_PARSING
		printf("[%s] -> SUBST ", str);
	#endif
	if (m->flag_redir)
	{
		ft_join_to_redir(str, cmd->redir);
		ft_set_env_flag(cmd, TRUE, REDIR);
	}
	else
	{
		ft_join_to_argv(str, cmd);
		ft_set_env_flag(cmd, TRUE, ARGV);
	}
	return (i + 1); // +1 car on compte le $
}
