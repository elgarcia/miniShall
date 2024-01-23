/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:34:41 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 22:48:14 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	print_str(const char *str, int i, int fd)
{
	if (str == NULL)
	{
		if (write(fd, "(null)", 6) == -1)
			return (-1);
		i += 6;
		return (i);
	}
	while (*str)
	{
		i = ft_putchar(*str, i, fd);
		if (i == -1)
			return (-1);
		str++;
	}
	return (i);
}
