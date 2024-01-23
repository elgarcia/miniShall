/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:01 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 22:42:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_putchar(char c, int i, int fd)
{
	if (i == -1)
		return (-1);
	if (write(fd, &c, 1) == -1)
		return (-1);
	i++;
	return (i);
}
