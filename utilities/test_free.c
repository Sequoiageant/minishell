/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:27:59 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/13 17:31:02 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str;

	str = strdup("test");
	free(str);
	str = NULL;
	printf("%s\n", str);
	return (0);
}