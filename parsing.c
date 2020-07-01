/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/07/01 15:25:34 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		backslash_activated(char *buf, t_state_machine *machine)
{
	if (machine->flag_quote)
		return (0);
	if (machine->flag_dquote)
	{
		if (buf[1] == '$' || buf[1] == '"' || buf[1] == '\\')
			return (1);
		else
			return (0);
	}
	return (1);
}

void	chose_state(char *buf, t_state_machine *machine)
{
	if (*buf == '"' && !machine->flag_quote)
		machine->state = FLAG;
	else if (*buf == '\'' && !machine->flag_dquote)
		machine->state = FLAG;
	else if (*buf == '\\' && backslash_activated(buf, machine))
		machine->state = BACKSLASH;
	else if (*buf == '$' && !machine->flag_quote)
		machine->state = DOLLAR;
	else if (*buf == ';' && !machine->flag_quote && !machine->flag_dquote)
		machine->state = MULTI;
	else if (*buf == '|' && !machine->flag_quote && !machine->flag_dquote)
		machine->state = PIPE;
	// else if ((*buf == '<' || *buf == '>') && !machine->flag_quote && !machine->flag_dquote)
	// 	machine->state = REDIR;
	else
		machine->state = LETTER;
}

int		parser(char *buf, t_list *env, t_list **pipe_list)
{
	t_state_machine		machine;
	static t_function	func[NB_STATE] = {fsm_letter, fsm_dollar, fsm_backslash, fsm_flag, fsm_multi, fsm_pipe};
	int					ret;
	
	
	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	while (*buf != '\0')
	{
		// printf("state: %d\n", machine.state);
		chose_state(buf, &machine);
		ret = func[machine.state](buf, &machine, env, pipe_list);
		if (ret == FAILURE)
			return (FAILURE);
		// printf("ret: %d\n", ret);
		buf += ret;
	}
	return (SUCCESS);
}


int		ft_parse(char *buf, t_list *env, t_list **pipe_list)
{
	if (add_pipe(pipe_list) == -1)
		return (EXIT_FAILURE);

	// pour print l'état initial du cmd->buf	
	// t_list *cmd_list;
	// t_list *p_list;
	// t_cmd *cmd;
	// p_list = *pipe_list;
	// while (p_list->next)
	// 	p_list = p_list->next;
	// cmd_list = (t_list*)p_list->content;
	// cmd = (t_cmd*)cmd_list->content;
	// printf("initial buf: [%s]\n", cmd->buf);
	
	if (parser(buf, env, pipe_list) == FAILURE)
		return (EXIT_FAILURE);
	if (filler(*pipe_list) == FAILURE)
		return (EXIT_FAILURE);
	// print_commands(*pipe_list);

	return (EXIT_SUCCESS);
}