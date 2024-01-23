/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:50:44 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 23:04:10 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	print_hex_address(unsigned long long x, int len, int fd)
{
	char	*hex;
	int		result[20];
	int		i;

	if (len == -1)
		return (-1);
	hex = "0123456789abcdef";
	i = 0;
	while (x >= 16)
	{
		result[i] = hex[x % 16];
		x = x / 16;
		i++;
	}
	result[i] = hex[x];
	while (i >= 0)
	{
		len = ft_putchar(result[i], len, fd);
		i--;
	}
	if (len == -1)
		return (-1);
	return (len);
}

int	print_address(void *ptr, int i, int fd)
{
	if (ptr == NULL)
	{
		if (write(fd, "0x0", 3) == -1)
			return (-1);
		i += 3;
		return (i);
	}
	i = print_str("0x", i, fd);
	i = print_hex_address((unsigned long long)ptr, i, fd);
	return (i);
}
