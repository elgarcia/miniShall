/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:32:48 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 23:04:40 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	unsigned_int(unsigned int nb, int i, int fd)
{
	if (nb > 9)
	{
		i = ft_putnbr(nb / 10, i, fd);
		i = ft_putnbr(nb % 10, i, fd);
	}
	else
		i = ft_putchar(nb + '0', i, fd);
	return (i);
}
