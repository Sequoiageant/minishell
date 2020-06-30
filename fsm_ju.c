/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_ju.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 19:47:20 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/30 10:01:46 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "minirt.h"

static int	error(t_data *data, char **tab, t_stm *machine)
{
	(void)data;
	if (tab[0][0] == '#')
	{
		return (MACHINE_CONTINUE);
	}
	else
	{
		machine->error |= TYPE_ERROR_MASK;
		return (MACHINE_ERROR);
	}
}

static int	set_obj(t_data *data, char **tab, t_stm *machine)
{
	static char		*str_obj[NB_OBJ] = {P_SP, P_PL, P_SQ, P_CY, P_TR};
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};
	static t_obj	*objlst;
	int				ret;
	int				i;

	i = 0;
	machine->error = 0;
	ret = FAILURE;
	while (i < NB_OBJ)
	{
		if (ft_strnequ(tab[0], str_obj[i], 2) == TRUE)
		{
			if (split_size_error(tab, i + NB_ENV, &machine->error))
				ret = func[i](tab, &objlst, data, machine);
			if (ret == SUCCESS)
				return (MACHINE_CONTINUE);
			else
				return (MACHINE_ERROR);
		}
		i++;
	}
	machine->state = ERROR;
	return (MACHINE_AGAIN);
}

static int	set_env(t_data *data, char **tab, t_stm *machine)
{
	static char		*str_env[NB_ENV] = {P_R, P_A, P_C, P_L};
	static t_func3	func[NB_ENV] = {set_res, set_al, set_cam, set_light};
	int				ret;
	int				i;

	i = 0;
	machine->error = 0;
	ret = FAILURE;
	while (i < NB_ENV)
	{
		if (ft_strcmp(tab[0], str_env[i]) == 0)
		{
			if (split_size_error(tab, i, &machine->error))
				ret = func[i](tab, data, machine);
			if (ret == SUCCESS)
				return (MACHINE_CONTINUE);
			else
				return (MACHINE_ERROR);
		}
		i++;
	}
	machine->state = OBJECT;
	return (MACHINE_AGAIN);
}

int	subst(char *buf, t_list *env t_stm *machine)
{
	(void)data;
	if (tab[0] == NULL)
	{
		return (MACHINE_CONTINUE);
	}
	machine->state = ENV;
	return (MACHINE_AGAIN);
}

int	subst(char *buf, t_list *env t_stm *machine)
{

	if (buf[0] == '"')
	{
		machine.subst = 1
		machine->state = letter;
	}
	else

	while (i < NB_SUBST)
	{
		if (*buf == str_subst[i])
		{
			machine->flag |= (1 << i) << 8;
			printf("[%c] -> CONV\n", str_subst[i]);
			machine->state = LETTER;
			print_bin(machine->flag);
			machine->flag = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

int			parser(char *buf)
{
	static t_func	func[NB_STATE] = {letter, quotes, db_quotes, back_slash, error};
	t_stm			*machine;
	int				ret;

	machine.state = SUBST;	
	machine.subst = 0;
	while (*buf != '\0')
	{
		ret = func[machine.state](buf, &machine);
		if (ret == FAILURE)
			return (FAILURE);
		buf += ret;
	}
	return (SUCCESS);
}

int			main(int ac, char **av)
{
	int		ret;

	ret = SUCCESS;
	if (ac == 2)
		ret = parser(av[1]);
	else
		printf("%s\n", "ERROR");;
	return (ret);
}*/