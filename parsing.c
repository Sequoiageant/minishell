/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/06/29 15:46:47 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		dollar(char *buf, t_state_machine *machine, t_list *env)
{
	int i;
	char *str;

	(void)env;
	i = 0;
	while(buf[i] != ' ' && buf[i])
		i++;
	str = ft_substr(buf, 0, i);
	printf("[%s] -> ENV\n", str);
	// printf("i: %d\n", i);
	if (buf[i] == ' ')
		i++;
	machine->state = LETTER;
	return(i);
}

int		backslash(char *buf, t_state_machine *machine, t_list *env)
{
	(void)machine;
	(void)env;
	printf("[%c] -> LETTER (ESCAPED)\n", buf[1]);
	return(2);
}

int		flag(char *buf, t_state_machine *machine, t_list *env)
{
	(void)env;
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

int		letter(char *buf, t_state_machine *machine, t_list *env)
{
	(void)machine;
	(void)env;
	printf("[%c] -> LETTER\n", *buf);
	return (1);
}

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
	else
		machine->state = LETTER;
}

int		parser(char *buf, t_list *env)
{
	t_state_machine		machine;
	static t_function	func[NB_STATE] = {letter, dollar, backslash, flag};
	int					ret;

	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	while (*buf != '\0')
	{
		// printf("state: %d\n", machine.state);
		chose_state(buf, &machine);
		ret = func[machine.state](buf, &machine, env);
		if (ret == FAILURE)
			return (FAILURE);
		// printf("ret: %d\n", ret);
		buf += ret;
	}
	return (SUCCESS);
}

int		ft_parse(char *buf, t_list *env, t_list **pipe_list)
{
	(void)pipe_list;
	if (parser(buf, env) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}