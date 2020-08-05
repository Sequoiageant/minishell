/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:55:37 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:09:59 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		sp_backslash(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)cmd;
	if (m->flag_redir)
		ft_join_to_redir(char_to_str(buf[0]), cmd->redir);
	else
		ft_join_to_argv(char_to_str(buf[0]), cmd);
	if (buf[1])
	{
		if (m->flag_redir)
		{
			ft_join_to_redir(char_to_str(buf[1]), cmd->redir);
			if (buf[1] == '$')
				ft_set_env_flag(cmd, FALSE, REDIR);
		}
		else
		{
			ft_join_to_argv(char_to_str(buf[1]), cmd);
			if (buf[1] == '$')
				ft_set_env_flag(cmd, FALSE, ARGV);
		}
		return (2);
	}
	return (1);
}

int		sp_flag_quote(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	if (m->flag_quote == ON)
		m->flag_quote = OFF;
	else
		m->flag_quote = ON;
	if (m->flag_redir)
		ft_join_to_redir(char_to_str(buf[0]), cmd->redir);
	else
		ft_join_to_argv(char_to_str(buf[0]), cmd);
	return (1);
}

int		sp_flag_dquote(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	if (m->flag_dquote == ON)
		m->flag_dquote = OFF;
	else
		m->flag_dquote = ON;
	if (m->flag_redir)
		ft_join_to_redir(char_to_str(buf[0]), cmd->redir);
	else
		ft_join_to_argv(char_to_str(buf[0]), cmd);
	return (1);
}

int		sp_flag_redir_on(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	int		offset;
	t_redir	*redir;
	
	redir = malloc(sizeof(t_redir));
	redir->file = ft_strdup("");
	redir->original = NULL;
	offset = set_redir_state(buf, &redir->state);
	m->flag_redir = ON;
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
	return (offset);
}

int		sp_flag_redir_off(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
	(void)m;
	(void)buf;
	(void)cmd;
	
	m->flag_redir = OFF;
	return (0);
	
}
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
	int		i;
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
