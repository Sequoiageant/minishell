/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:51:08 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/03 14:00:32 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		f_line(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_read(char **buf, int fd)
{
	int ret;

	if (BUFFER_SIZE == 0)
		return (-1);
	if (!(*buf = malloc((BUFFER_SIZE + 1) * sizeof(*buf))))
		return (-1);
	ret = read(fd, *buf, BUFFER_SIZE);
	if (ret == -1)
		return (-1);
	buf[0][ret] = 0;
	if (!ret)
	{
		free(*buf);
		*buf = 0;
	}
	return (ret);
}

int		ft_len(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int		ft_cat(char **str, char *buf, int ret)
{
	char	*tmp;
	int		i;
	int		j;
	int		len;

	tmp = *str;
	len = ft_len(*str);
	if (!(*str = malloc(len + ret + 1)))
	{
		if (tmp)
			free(tmp);
		free(buf);
		return (-1);
	}
	i = -1;
	while (++i < len)
		str[0][i] = tmp[i];
	j = -1;
	while (buf[++j])
		str[0][i + j] = buf[j];
	str[0][i + j] = 0;
	if (tmp)
		free(tmp);
	free(buf);
	return (0);
}

int		ft_clean(int ret, t_fd **begin, t_fd **elem, int error)
{
	t_fd	*tmp;

	if (*elem == *begin)
		*begin = (*elem)->next;
	else
	{
		tmp = *begin;
		while (tmp->next != *elem)
			tmp = tmp->next;
		tmp->next = (*elem)->next;
	}
	if ((*elem)->str)
	{
		free((*elem)->str);
		(*elem)->str = 0;
	}
	free(*elem);
	if (error == -1)
		return (-1);
	return (ret);
}
