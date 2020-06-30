/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/06/30 10:39:16 by grim             ###   ########.fr       */
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
	else if (*buf == ';' && !machine->flag_quote)
		machine->state = MULTI;
	else
		machine->state = LETTER;
}

int		parser(char *buf, t_list *env, t_list **pipe_list)
{
	t_state_machine		machine;
	static t_function	func[NB_STATE] = {letter, dollar, backslash, flag, multi};
	int					ret;
	t_pipeline 			*pipe;
	
	
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
	
		// juste pour faire des printf du pipe_buf
		while ((*pipe_list)->next)
			*pipe_list = (*pipe_list)->next;
		pipe = (t_pipeline*)(*pipe_list)->content;
		printf(" pipe_buf: [%s]\n", pipe->pipe_buf);
		//
	}
	// fill_pipe(pipe);
	return (SUCCESS);
}


int		ft_parse(char *buf, t_list *env, t_list **pipe_list)
{
	if (add_pipe(pipe_list) == -1)
		return (EXIT_FAILURE);
	
	// t_pipeline *pipe;
	// char	*pipe_buf;
	// pipe = (t_pipeline*)(*pipe_list)->content;
	// pipe_buf = pipe->pipe_buf;
	// printf("p_buf: %s\n", pipe_buf);

	if (parser(buf, env, pipe_list) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}