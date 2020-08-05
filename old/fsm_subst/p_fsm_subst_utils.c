/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 10:46:01 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 10:53:35 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_join_to_cmd_buf2(char *str, t_cmd *cmd)
{
	char	*tmp;

	tmp = cmd->buf;
	if ((cmd->buf = ft_strjoin(tmp, str)) == NULL)
		return (FAILURE);
	free(tmp);
	free(str);
	#ifdef DEBUG_PARSING
		printf("buf: [%s]\n", cmd->buf);
	#endif
	return (SUCCESS);
}

int     variable_substitution(t_cmd *cmd, t_key_val *key_val)
{
	if (key_val)
	{
		if ((ft_join_to_cmd_buf2(ft_strdup(key_val->val), cmd) == FAILURE))
			return (FAILURE);
	}
	return (SUCCESS);
}

int		ft_is_dollar_start(char c)
{
	if (c == '?' || c == '_' || ft_isalpha(c))
		return (TRUE);
	else
		return (FALSE);
}

int		count_dollar_char(char *buf)
{
	int i;

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