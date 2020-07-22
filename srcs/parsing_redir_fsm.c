/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/22 19:23:11 by grim             ###   ########.fr       */
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
		ft_join_to_redir(char_to_str(buf[1]), cmd->redir);
	else
		ft_join_to_buf(char_to_str(buf[1]), &cmd->buf);
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
	// on desactive le flag redir lorsqu'on rencontre un espace ou un tab non "escapés"
	if (m->flag_redir && !m->flag_quote && !m->flag_dquote &&
	(*buf == 9 || *buf == 32))
	{
		m->flag_redir = 0;
		#ifdef DEBUG_PARSING
			printf("--REDIR OFF \n");
		#endif
	}	
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER ", *buf);
	#endif
	if (m->flag_redir)
		ft_join_to_redir(char_to_str(buf[0]), cmd->redir);
	else
		ft_join_to_buf(char_to_str(buf[0]), &cmd->buf);
	return (1);
}

// void	count_redir_char(int *start, int *len, char *str)
// {
// 	int ret;

// 	if (str[0] == '>' && str[1] == '>')
// 		ret = 2;
// 	else
// 		ret = 1;
// 	while (str[ret] == 0 || str[ret] == 9 || str[ret] == 32)
// 		ret++;
// 	*start = ret;
// 	printf("c: %c\n", str[ret]);
// 	while (str[ret] != 9 && str[ret] != 32 && str[ret] != '>' && str[ret] != '<' && str[ret] != 0) // space et tab, les deux "IFS" par défaut (avec le \n, mais NA)
// 		ret++;
// 	*len = ret - *start;
// }

// int red_redir(t_fsm_redir *m, char *buf, t_cmd *cmd)
// {
// 	int len;
// 	int	start;
	
// 	(void)m;
// 	(void)cmd;
// 	#ifdef DEBUG_PARSING
// 		printf("[%c] -> REDIR \n", *buf);
// 	#endif
// 	count_redir_char(&start, &len, buf);
// 	printf("len: %d\n", len);
// 	printf("start: %d\n", start);
// 	printf("redir path: [%s]\n", ft_substr(buf, start, len));
// 	return (start + len);
// }