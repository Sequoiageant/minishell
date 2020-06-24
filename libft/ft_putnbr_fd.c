/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:24:36 by bbrunet           #+#    #+#             */
/*   Updated: 2019/11/13 12:04:41 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbr(int nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		ft_nbr(-nb, fd);
	}
	else if (nb != 0)
	{
		ft_nbr(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_nbr(-214748364, fd);
		ft_putchar_fd('8', fd);
	}
	else if (n == 0)
	{
		ft_putchar_fd('0', fd);
	}
	else
		ft_nbr(n, fd);
}
