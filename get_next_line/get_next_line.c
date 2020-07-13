/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:41:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/13 20:16:44 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	ft_strjoin_back(char *back, char **src)
{
	char *tmp;

	if (back == NULL)
		return ;
	if (*src)
	{
		tmp = ft_strdup(*src);
		free(*src);
		*src = NULL;
	}
	else
		tmp = ft_strdup("");
	*src = ft_strjoin(tmp, back);
	free(tmp);
	tmp = NULL;
}

static	int		ft_strchr_pos(const char *s, int c)
{
	size_t pos;

	if (!s)
		return (FAILURE);
	pos = 0;
	while (*s != c)
	{
		if (*s == '\0')
			return (FAILURE);
		s++;
		pos++;
	}
	return (pos);
}

static	int		ft_read_line(char **str, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;

	ret = 1;
	while (ft_strchr_pos(*str, '\n') == FAILURE && ret > 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[ret] = '\0';
			ft_strjoin_back(buf, str);
		}
	}
	return (ret);
}

static	int		ft_fill_line(char **line, char **str)
{
	ssize_t	pos;
	char	*tmp;

	pos = 0;
	if ((pos = ft_strchr_pos(*str, '\n')) != FAILURE)
	{
		*line = ft_substr(*str, 0, pos);
		tmp = ft_strdup(*str);
		free(*str);
		*str = NULL;
		*str = ft_strdup(tmp + pos + 1);
		free(tmp);
		tmp = NULL;
		return (AGAIN);
	}
	else
	{
		*line = *str;
		return (SUCCESS);
	}
	return (FAILURE);
}

int				get_next_line(int fd, char **line)
{
	static char	*str;
	int			ret;

	ret = FAILURE;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (FAILURE);
	ret = ft_read_line(&str, fd);
	if (ret != FAILURE)
		ret = ft_fill_line(line, &str);
	return (ret);
}
