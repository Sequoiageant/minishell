/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:58:58 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 09:38:57 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		dollar(char *buf, t_state_machine *machine, t_list *env, t_list **pipe_list)
{
	int i;
	char *str;
    t_key_val *key_val;

    (void)pipe_list;
    (void)machine;
	// print_env_elem(env, "PWD");
    // ft_print_env(env);
	buf++;
    i = 0;
	while(buf[i] != 0 && !ft_is_special(buf[i]))
		i++;
	str = ft_substr(buf, 0, i);
    key_val = find_key_val(env, str);
    if (key_val)
    {
	    printf("[%s] -> ENV\n", key_val->val);
        ft_join_str_to_pipe(key_val->val, *pipe_list);
    }
	else
        printf("[NULL] -> ENV\n");
    return(i + 1); // + 1 car il y a le '$'
}