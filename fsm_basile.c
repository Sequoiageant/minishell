#include "fsm.h"

// int		ft_strnequ(char *s1, char *s2, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (i < n && s2[i] != '\0')
// 	{
// 		if (s1[i] != s2[i])
// 			return (FALSE);
// 		i++;
// 	}
// 	return (TRUE);
// }


// void	print_bin(int nb)
// {
// 	int	i;

// 	i = 0;
// 	printf("flag : [");
// 	while (i < 32)
// 	{
// 		if (i != 0 && i % 8 == 0)
// 			printf(".");
// 		if (nb & (1 << (31 - i)))
// 			printf("1");
// 		else
// 			printf("0");
// 		i++;
// 	}
// 	printf("]\n");
// }



// ////////////////////////////////////////////////////

// int	error(char *format, t_state_machine *machine)
// {
// 	printf("[%c] -> ERROR\n", *format);
// 	machine->state = LETTER;
// 	machine->flag = 0;
// 	print_bin(machine->flag);
// 	return (1);
// }

// int	conv(char *format, t_state_machine *machine)
// {
// 	static char	str_conv[NB_CONV] = STR_CONV;
// 	int			i;

// 	i = 0;
// 	while (i < NB_CONV)
// 	{
// 		if (*format == str_conv[i])
// 		{
// 			machine->flag |= (1 << i) << 8;
// 			printf("[%c] -> CONV\n", str_conv[i]);
// 			machine->state = LETTER;
// 			print_bin(machine->flag);
// 			machine->flag = 0;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	machine->state = ERROR;
// 	return (0);
// }


// int	flag(char *format, t_state_machine *machine)
// {
// 	static char	*str_flag[NB_FLAG] = {F_HH, F_LL, F_H, F_L, F_HASH, F_ZERO};
// 	int			len;
// 	int			i;

// 	i = 0;
// 	while (i < NB_FLAG)
// 	{
// 		len = (i < 2) ? 2 : 1;
// 		if (ft_strnequ(format, str_flag[i], len) == TRUE)
// 		{
// 			printf("[%s] -> FLAG\n", str_flag[i]);
// 			machine->flag |= (1 << i);
// 			return (len);
// 		}
// 		i++;
// 	}
// 	machine->state = CONV;
// 	return (0);
// }

// int	dollar(char *format, t_state_machine *machine)
// {
// 	if (*format == CHAR_FORMAT)
// 		machine->state = FLAG;
// 	else
// 		printf("[%c] -> LETTER\n", *format);
// 	return (1);
// }

// int	quote(char *format, t_state_machine *machine)
// {
// 	if (*format == CHAR_FORMAT)
// 		machine->state = FLAG;
// 	else
// 		printf("[%c] -> LETTER\n", *format);
// 	return (1);
// }

int dollar(char *buf, t_state_machine *machine)
{
	ft_convert(buf);
	
}

int	backslash(char *buf, t_state_machine *machine)
{
	if (machine->flag_quote == 1 || machine->flag_backslash == 1)
		return(1);
	else
		machine->flag_backslash = 1;
	return(1);
}

int	quote(char *buf, t_state_machine *machine)
{
	if (machine->flag_backslash == 1)
	{
		machine->flag_backslash = 0;
		return (1);
	}
	if (machine->flag_quote == 0)
		machine->flag_quote = 1;
	else
		machine->flag_quote = 0;
	return(1);
}

int	dquote(char *buf, t_state_machine *machine)
{
	if (machine->flag_backslash == 1)
	{
		machine->flag_backslash = 0;
		return (1);
	}
	if (machine->flag_dquote == 0)
		machine->flag_dquote = 1;
	else
		machine->flag_dquote = 0;
	return(1);
}

int	letter(char *buf, t_state_machine *machine)
{
	if (*buf == '"')
		machine->state = DOUBLE_Q;
	else if (*buf == '\'')
		machine->state = QUOTE;
	else if (*buf == '\\')
		machine->state = BACKSLASH;
	else if (*buf == '$')
		machine->state = DOLLAR;
	else
		if (machine->flag_backslash == 1) // le / ne doit s'appliquer qu'au caractère suivant
			machine->flag_backslash = 0;
	 	printf("[%c] -> LETTER\n", *buf);
 	return (1);
}

int	parser(char *buf)
{
	t_state_machine		machine;
	static t_function	func[NB_STATE] = {letter, quote, dquote, dollar};
	int					ret;

	machine.state = NORMAL;	
	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	machine.flag_backslash = 0;
	machine.backslash_activated = 0;
	while (*buf != '\0')
	{
		ret = func[machine.state](buf, &machine);
		if (ret == FAILURE)
			return (FAILURE);
		buf += ret;
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac != 2 || parser(av[1]) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
