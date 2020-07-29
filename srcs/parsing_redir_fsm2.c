/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_fsm2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:57:07 by grim              #+#    #+#             */
/*   Updated: 2020/07/29 12:02:24 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int red_flag_redir_on(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	int		offset;
	t_redir	*redir;
	
	// init le t_redir suivant de la chaine et set le redir->state en fonction du signe < > ou >>
	redir = malloc(sizeof(t_redir));
	redir->file = ft_strdup(""); // pour permettre les str_join
	offset = set_redir_state(buf, &redir->state);
	#ifdef DEBUG_PARSING
		if (redir->state == REDIR_OUT)
			printf("--REDIR OUT ACTIVATED \n");
		if (redir->state == REDIR_APPEND)
			printf("--REDIR APPEND ACTIVATED \n");
		if (redir->state == REDIR_IN)
			printf("--REDIR IN ACTIVATED \n");
	#endif
	// active le flag_redir
	m->flag_redir = ON;
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
	return (offset);
}

int red_flag_redir_off(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	
	(void)m;
	(void)buf;
	(void)cmd;
	
	m->flag_redir = OFF;
	#ifdef DEBUG_PARSING
		printf("--REDIR OFF \n");
	#endif
	return (0);
}

int red_whitespace(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	int ret;
	
	(void)m;
	(void)cmd;
	ret = 0;
	while (buf[ret] == TAB || buf[ret] == SPACE)
		ret++;
	#ifdef DEBUG_PARSING
		printf("[ ] -> %d WHITESPACE(S) ", ret);
	#endif
	if (ft_is_special(buf[ret]) == FALSE) // on ajoute un arg sauf si après l'espace c'est la fin de la commande, ou un caractère de redir...
	{
		ft_lstadd_back(&cmd->argv_list, ft_lstnew(ft_strdup(""))); 
		#ifdef DEBUG_PARSING
			printf("--> NEW ARGV \n");
		#endif
	}
	return (ret);
}

int	red_dollar(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	int		i;
	char	*str;

	(void)m;
	i = count_dollar_char(buf);
	str = ft_substr(buf, 0, i + 1); // +1 car on compte le $
	#ifdef DEBUG_PARSING
		printf("[%s] -> SUBST ", str);
	#endif
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
	return (i + 1); // +1 car on compte le $
}
