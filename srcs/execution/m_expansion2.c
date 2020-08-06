/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_expansion2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:04:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/06 11:02:06 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void			ft_realloc_or_free(char **final, char **src)
{
	if (ft_strlen(*final) == 0)
	{
		ft_str_free(src);
		ft_str_free(final);
	}
	else
		ft_realloc(final, src);
}

static char		*preserve_quotes(char *str)
{
	char	*new;
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	new = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
			ft_join_to_str(char_to_str('\\'), &new);
		ft_join_to_str(char_to_str(str[i]), &new);
		i++;
	}
	return (new);
}

static size_t	substitute_dollar(char **str, t_list *env)
{
	size_t		i;
	char		*tmp;
	char		*ret;
	t_key_val	*key_val;

	ret = NULL;
	i = count_dollar_char(*str);
	tmp = ft_substr(*str, 1, i);
	if (tmp)
	{
		if (tmp[0] == '?')
			ret = ft_itoa(g_glob.ret);
		else
		{
			key_val = find_key_val(env, tmp);
			if (key_val)
				ret = preserve_quotes(key_val->val);
			else
				ret = ft_strdup("");
		}
		if (ret)
			ft_realloc(&ret, str);
		free(tmp);
	}
	return (i);
}

int				ft_handle_argv(char **tmp, t_list *env, t_list **flag, int *ret)
{
	size_t	len;

	len = 0;
	if ((*tmp)[0] == '$')
	{
		if (*(int *)(*flag)->content == TRUE)
		{
			len = substitute_dollar(tmp, env);
			*ret = TRUE;
		}
		else
			len = ft_strlen(*tmp) - 1;
		(*flag) = (*flag)->next;
	}
	else
		len = ft_strlen(*tmp) - 1;
	return (len);
}
