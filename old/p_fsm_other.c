/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:55:50 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 09:30:27 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

// static	int	variable_substitution(t_list **p_list, t_key_val *key_val)
// {
// 	if (key_val)
// 	{
// 		if ((ft_join_to_cmd_buf(ft_strdup(key_val->val), *p_list) == FAILURE))
// 			return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

// int			fsm_dollar(char *buf, t_state_machine *m, t_list *env, t_list **p_list)
// {
// 	int			i;
// 	char		*str;
// 	t_key_val	*key_val;

// 	(void)p_list;
// 	(void)m;
// 	buf++;
// 	i = count_dollar_char(buf);
// 	str = ft_substr(buf, 0, i);
// 	if (str[0] == '?')
// 	{
// 		#ifdef DEBUG_PARSING
// 		printf("[$%s] -> ENV ", str);
// 		#endif
// 		free(str);
// 		if ((ft_join_to_cmd_buf(ft_strdup("?"), *p_list) == FAILURE))
// 			return (FAILURE);
// 	}
// 	else
// 	{
// 		key_val = find_key_val(env, str);
// 		#ifdef DEBUG_PARSING
// 		printf("[$%s] -> ENV ", str);
// 		#endif
// 		free(str);
// 		if (variable_substitution(p_list, key_val) == FAILURE)
// 			return (FAILURE);
// 		#ifdef DEBUG_PARSING
// 			if (key_val == NULL)
// 				printf("buf: unchanged\n");
// 		#endif
// 	}
// 	return (i + 1); // + 1 car il y a le '$'
// }
