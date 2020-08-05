/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_subst2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:54:48 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 14:48:48 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		su_backslash(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env)
{
	(void)m;
	(void)env;
	
	#ifdef DEBUG_PARSING
		printf("[%c] -> ESCAPED LETTER ", buf[1]);
	#endif
	
	ft_join_to_cmd_buf2(char_to_str(buf[0]), cmd);
	if (buf[1])
	{
		ft_join_to_cmd_buf2(char_to_str(buf[1]), cmd);
		return (2);
	}
	else
		return (1); // si on a un backslash en fin de commande, pour ne pas causer de "invalid read"
}

int		su_flag_quote(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env)
{
	(void)env;
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
	ft_join_to_cmd_buf2(char_to_str(buf[0]), cmd);
	return (1);	
}

int		su_flag_dquote(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env)
{
	(void)env;
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
	ft_join_to_cmd_buf2(char_to_str(buf[0]), cmd);
	return (1);	
}

int		su_letter(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env)
{
	(void)m;
	(void)env;
	#ifdef DEBUG_PARSING
		printf("[%c] -> LETTER ", *buf);
	#endif
	ft_join_to_cmd_buf2(char_to_str(*buf), cmd);
	return (1);
}

int		su_subst(t_fsm_cmd *m, char *buf, t_cmd *cmd, t_list *env )
{
	
	int			i;
	char		*str;
	t_key_val	*key_val;

	(void)m;
	i = count_dollar_char(buf);
	str = ft_substr(buf, 1, i);
	if (str[0] == '?')
	{
		#ifdef DEBUG_PARSING
		printf("[$%s] -> ENV ", str);
		#endif
		free(str);
		ft_join_to_cmd_buf2(ft_itoa(g_glob.ret), cmd);
	}
	else
	{
		key_val = find_key_val(env, str);
		#ifdef DEBUG_PARSING
		printf("[$%s] -> ENV ", str);
		#endif
		free(str);
		if (variable_substitution(cmd, key_val) == FAILURE)
			return (FAILURE);
		#ifdef DEBUG_PARSING
			if (key_val == NULL)
				printf("buf: unchanged\n");
		#endif
	}
	return (i + 1); // + 1 car il y a le '$'
}
