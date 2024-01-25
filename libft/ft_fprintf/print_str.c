/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:34:41 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 23:04:32 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

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
