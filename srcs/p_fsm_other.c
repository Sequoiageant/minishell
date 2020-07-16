/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/07/16 11:51:47 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		fsm_backslash(char *buf, t_state_machine *m, t_list *e, t_list **p_list)
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

int		fsm_flag(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
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

int		fsm_letter(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
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

int		fsm_dollar(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
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
		if ((ft_join_to_cmd_buf(ft_itoa(g_glob.ret), *p_list) == FAILURE)) // on envoie une copie de key_val->val, pour pouvoir la free sans modifier la t_list *env
				return (FAILURE); 
	}
	else
	{
		key_val = find_key_val(env, str);
	#ifdef DEBUG_PARSING
		printf("[$%s] -> ENV ", str);
	#endif
		free(str);
		if (key_val)
		{
			if ((ft_join_to_cmd_buf(ft_strdup(key_val->val), *p_list) == FAILURE)) // on envoie une copie de key_val->val, pour pouvoir la free sans modifier la t_list *env
				return (FAILURE); 
		}
	}
	return (i + 1); // + 1 car il y a le '$'
}
