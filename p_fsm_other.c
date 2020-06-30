/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_flag_backslash_letter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 16:20:07 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		fsm_backslash(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	(void)machine;
	(void)env;
	printf("[%c] -> LETTER (ESCAPED) ", buf[1]);
	ft_join_to_cmd_buf(char_to_str(buf[1]), *pipe_list);
	return(2);
}

int		fsm_flag(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	(void)env;
	(void)pipe_list;
	if (*buf == '"')
	{
		if (machine->flag_dquote)
			machine->flag_dquote = 0;
		else
			machine->flag_dquote = 1;
	}
	else
	{
		if (machine->flag_quote)
			machine->flag_quote = 0;
		else
			machine->flag_quote = 1;
	}
	return (1);
}

int		fsm_letter(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	(void)machine;
	(void)env;
	printf("[%c] -> LETTER ", *buf);
	ft_join_to_cmd_buf(char_to_str(*buf), *pipe_list);
	return (1);
}

int		fsm_dollar(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	int i;
	char *str;
    t_key_val *key_val;

    (void)pipe_list;
    (void)machine;
	buf++;
    i = 0;
	while(buf[i] != 0 && !ft_is_special(buf[i]))
		i++;
	str = ft_substr(buf, 0, i);
    key_val = find_key_val(env, str);
	printf("[$%s] -> ENV ", str);
    if (key_val)
        ft_join_to_cmd_buf(ft_strdup(key_val->val), *pipe_list); // on envoie une copie de key_val->val, pour pouvoir la free sans modifier la t_list *env
    return(i + 1); // + 1 car il y a le '$'
}
