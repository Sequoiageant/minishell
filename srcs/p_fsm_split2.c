/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:55:37 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 14:20:48 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		sp_backslash(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)cmd;
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER ", buf[1]);
	#endif
	if (buf[1] == 0) // cas ou on a un / en fin de commande
		return (1);
	if (m->flag_redir)
		ft_join_to_redir(char_to_str(buf[1]), cmd->redir);
	else
		ft_join_to_argv(char_to_str(buf[1]), cmd);
	return (2);
}

int		sp_flag_quote(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
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

}
int		sp_flag_dquote(t_fsm_cmd *m, char *buf, t_cmd *cmd)
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

int		sp_flag_redir_on(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	int		offset;
	t_redir	*redir;
	
	// init le t_redir suivant de la chaine et set le redir->state en fonction du signe < > ou >>
	redir = malloc(sizeof(t_redir));
	redir->file = ft_strdup(""); // pour permettre les str_join
	redir->original = NULL;
	offset = set_redir_state(buf, &redir->state);
	#ifdef DEBUG_PARSING
		if (redir->state == REDIR_OUT)
			printf("--REDIR OUT ACTIVATED \n");
		if (redir->state == REDIR_APPEND)
			printf("--REDIR APPEND ACTIVATED \n");
		if (redir->state == REDIR_IN)
			printf("--REDIR IN ACTIVATED \n");
	#endif
	// active le flag_redir
	m->flag_redir = ON;
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
	return (offset);
}

int		sp_flag_redir_off(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)buf;
	(void)cmd;
	
	m->flag_redir = OFF;
	#ifdef DEBUG_PARSING
		printf("--REDIR OFF \n");
	#endif
	return (0);
	
}
int		sp_letter(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	(void)m;
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER ", *buf);
	#endif
	if (m->flag_redir)
		ft_join_to_redir(char_to_str(buf[0]), cmd->redir);
	else
		ft_join_to_argv(char_to_str(buf[0]), cmd);
	return (1);
}
	
int		sp_whitespace(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	int ret;
	
	(void)m;
	(void)cmd;
	ret = 0;
	while (buf[ret] == TAB || buf[ret] == SPACE)
		ret++;
	#ifdef DEBUG_PARSING
		printf("[ ] -> %d WHITESPACE(S) ", ret);
	#endif
	if (ft_is_special(buf[ret]) == FALSE) // on ajoute un arg sauf si après l'espace c'est la fin de la commande, ou un caractère de redir...
	{
		ft_lstadd_back(&cmd->argv_list, ft_lstnew(ft_strdup(""))); 
		#ifdef DEBUG_PARSING
			printf("--> NEW ARGV \n");
		#endif
	}
	return (ret);
}