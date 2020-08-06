/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:01:51 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 11:08:06 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int		sp_letter(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	(void)m;
	if (m->flag_redir)
	{
		ft_join_to_redir(char_to_str(buf[0]), cmd->redir);
		if (buf[0] == '$')
			ft_set_env_flag(cmd, FALSE, REDIR);
	}
	else
	{
		ft_join_to_argv(char_to_str(buf[0]), cmd);
		if (buf[0] == '$')
			ft_set_env_flag(cmd, FALSE, ARGV);
	}
	return (1);
}

int		sp_whitespace(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	int ret;

	(void)m;
	(void)cmd;
	ret = 0;
	while (buf[ret] == TAB || buf[ret] == SPACE)
		ret++;
	if (ft_is_special(buf[ret]) == FALSE)
		ft_lstadd_back(&cmd->argv_list, ft_lstnew(ft_strdup("")));
	return (ret);
}

int		sp_dollar(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	size_t	i;
	char	*str;

	(void)m;
	i = count_dollar_char(buf);
	str = ft_substr(buf, 0, i + 1);
	if (m->flag_redir)
	{
		ft_join_to_redir(str, cmd->redir);
		ft_set_env_flag(cmd, TRUE, REDIR);
	}
	else
	{
		ft_join_to_argv(str, cmd);
		ft_set_env_flag(cmd, TRUE, ARGV);
	}
	return (i + 1);
}
