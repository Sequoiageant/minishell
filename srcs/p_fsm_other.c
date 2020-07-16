/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/07/16 17:00:30 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int			fsm_backslash(char *buf, t_state_machine *m, t_list *e, t_list **p_list)
{
	(void)m;
	(void)e;
	#ifdef DEBUG_PARSING
	printf("[%c] -> LETTER ", *buf);
	#endif

	if (ft_join_to_cmd_buf(char_to_str(buf[1]), *p_list) == FAILURE)
		return (FAILURE);
	return (2);
}

int			fsm_flag(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)env;
	(void)p_list;
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

int			fsm_letter(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	(void)m;
	(void)env;
	#ifdef DEBUG_PARSING
	printf("[%c] -> LETTER ", *buf);
	#endif
	if ((ft_join_to_cmd_buf(char_to_str(*buf), *p_list) == FAILURE))
		return (FAILURE);
	return (1);
}

static	int	variable_substitution(t_list **p_list, t_key_val *key_val)
{
	if (key_val)
	{
		if ((ft_join_to_cmd_buf(ft_strdup(key_val->val), *p_list) == FAILURE))
			return (FAILURE);
	}
	return (SUCCESS);
}

int			fsm_dollar(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
{
	int			i;
	char		*str;
	t_key_val	*key_val;

	(void)p_list;
	(void)m;
	buf++;
	i = 0;
	while (buf[i] && !ft_is_special(buf[i]))
		i++;
	str = ft_substr(buf, 0, i);
	if (str[0] == '?')
	{
		free(str);
		if ((ft_join_to_cmd_buf(ft_itoa(g_glob.ret), *p_list) == FAILURE))
			return (FAILURE);
	}
	else
	{
		key_val = find_key_val(env, str);
		free(str);
		if (variable_substitution(p_list, key_val) == FAILURE)
			return (FAILURE);
	}
	return (i + 1); // + 1 car il y a le '$'
}
