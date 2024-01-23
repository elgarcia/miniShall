/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:33:54 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 23:04:19 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
/*
int	to_hex(unsigned char c, int i, int checker)
{
	char	*base;

	if (checker == 1)
	{
		base = "0123456789abcdef";
		i = ft_putchar(base[c / 16], i);
		i = ft_putchar(base[c % 16], i);
	}
	else
	{
		base = "0123456789ABCDEF";
		i = ft_putchar(base[c / 16], i);
		i = ft_putchar(base[c % 16], i);
	}
	return (i);
}
*/
int	print_hex(unsigned int x, int len, int c, int fd)
{
	char	*hex;
	int		result[20];
	int		i;

	if (c == 1)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
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
		if (len == -1)
			return (-1);
		i--;
	}
	return (len);
}
