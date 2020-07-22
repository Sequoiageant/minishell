/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/22 15:52:48 by grim             ###   ########.fr       */
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

int ft_join_to_redir(char *added_str, t_list *redir_list)
{
    char	*tmp;
	t_redir	*redir;
 
	while (redir_list->next)
		redir_list = redir_list->next;
	redir = (t_redir*)redir_list->content;
    tmp = redir->file;
	if ((redir->file = ft_strjoin(tmp, added_str)) == NULL)
		return (FAILURE);
    free(tmp);
    free(added_str);
    #ifdef DEBUG_PARSING
		printf("file: [%s]\n", redir->file);
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
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER ", *buf);
	#endif
	// on desactive le flag redir lorsqu'on rencontre un espace ou un tab non "escapés"
	if (m->flag_redir && !m->flag_quote && !m->flag_dquote &&
	(*buf == 9 || *buf == 32))
		m->flag_redir = 0;
	
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