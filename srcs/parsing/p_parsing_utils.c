/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parsing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:34:41 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 11:06:23 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int		ft_is_special(char c)
{
	if (c == ';' || c == '>'
	|| c == '<' || c == '|' || c == 0)
		return (TRUE);
	else
		return (FALSE);
}

int		ft_join_to_cmd_buf(char *str, t_list *pipe_list)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	char	*tmp;

	while (pipe_list->next)
		pipe_list = pipe_list->next;
	cmd_list = (t_list*)pipe_list->content;
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd = (t_cmd*)cmd_list->content;
	tmp = cmd->buf;
	if ((cmd->buf = ft_strjoin(tmp, str)) == NULL)
		return (FAILURE);
	free(tmp);
	free(str);
	return (1);
}

char	*char_to_str(char c)
{
	char *str;

	str = malloc(2);
	str[0] = c;
	str[1] = 0;
	return (str);
}

int		ft_is_dollar_start(char c)
{
	if (c == '?' || c == '_' || ft_isalpha(c))
		return (TRUE);
	else
		return (FALSE);
}

size_t	count_dollar_char(char *buf)
{
	size_t i;

	i = 1;
	if (buf[1] == '?')
		return (1);
	else
	{
		while (ft_isalnum(buf[i]) || buf[i] == '_')
			i++;
	}
	return (i - 1);
}
