#include "fsm.h"
#include "libft.h"
#include "mshell.h"

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

int		ft_parse_fsm(char *buf, t_list *env)
{
	if (parser(buf, env) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
