/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:50:49 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/24 12:28:58 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sub(char **dst, char *src, int start, int len)
{
	int i;

	if (!(*dst = malloc((len + 1) * sizeof(**dst))))
		return (-1);
	i = 0;
	while (i < len)
	{
		dst[0][i] = src[start + i];
		i++;
	}
	dst[0][i] = 0;
	return (0);
}

int		ft_cut(char **str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[0][i] != '\n')
		i++;
	if (ft_sub(line, *str, 0, i) == -1)
	{
		free(*str);
		*str = 0;
		return (-1);
	}
	tmp = *str;
	if (ft_sub(str, tmp, i + 1, ft_len(*str) - i - 1) == -1)
	{
		free(tmp);
		tmp = 0;
		return (-1);
	}
	free(tmp);
	return (0);
}

int		add_list(int fd, t_fd **begin, t_fd **elem)
{
	t_fd	*tmp;

	if (!(*elem = malloc(sizeof(**elem))))
		return (-1);
	(*elem)->fd = fd;
	(*elem)->str = 0;
	(*elem)->next = NULL;
	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *elem;
		return (0);
	}
	*begin = *elem;
	return (0);
}

int		scan_list(int fd, t_fd **begin, t_fd **elem)
{
	t_fd	*tmp;

	tmp = *begin;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			*elem = tmp;
			return (1);
		}
		tmp = tmp->next;
	}
	if (add_list(fd, begin, elem) == -1)
		return (-1);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_fd		*begin;
	t_fd			*elem;
	char			*buf;
	int				ret;
	int				cat;

	ret = 0;
	cat = 0;
	if (scan_list(fd, &begin, &elem) == -1)
		return (-1);
	while (fd >= 0 && line && !f_line(elem->str) && (ret = ft_read(&buf, fd)) &&
ret != -1 && (cat = ft_cat(&elem->str, buf, ret)) != -1)
		fd = fd + 0;
	if (ret == -1 || cat == -1 || fd < 0 || !line)
		return (ft_clean(-1, &begin, &elem, 0));
	if (elem->str && !ret && !(f_line(elem->str)))
	{
		cat = ft_sub(line, elem->str, 0, ft_len(elem->str));
		return (ft_clean(1, &begin, &elem, cat));
	}
	if (elem->str == 0)
		return (0);
	if (ft_cut(&elem->str, line) == -1)
		return (ft_clean(-1, &begin, &elem, 0));
	return (1);
}
