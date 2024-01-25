/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:36:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 23:03:49 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_putnbr(int nb, int i, int fd)
{
	if (i == -1)
		return (-1);
	if (nb <= -2147483648)
	{
		i = ft_putchar('-', i, fd);
		i = ft_putchar('2', i, fd);
		i = ft_putnbr(147483648, i, fd);
	}
	else if (nb < 0)
	{
		i = ft_putchar('-', i, fd);
		i = ft_putnbr(-nb, i, fd);
	}
	else if (nb > 9)
	{
		i = ft_putnbr(nb / 10, i, fd);
		i = ft_putnbr(nb % 10, i, fd);
	}
	else
		i = ft_putchar(nb + '0', i, fd);
	return (i);
}
