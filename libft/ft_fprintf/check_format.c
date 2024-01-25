/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:31:25 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 23:03:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	check_format(va_list args, const char *format, int i, int j, int fd)
{
	if (format[j] == 'c')
		i = ft_putchar(va_arg(args, int), i, fd);
	else if (format[j] == 's')
		i = print_str(va_arg(args, char *), i, fd);
	else if (format[j] == 'p')
		i = print_address(va_arg(args, void *), i, fd);
	else if (format[j] == 'd')
		i = ft_putnbr(va_arg(args, int), i, fd);
	else if (format[j] == 'i')
		i = ft_putnbr(va_arg(args, int), i, fd);
	else if (format[j] == 'u')
		i = unsigned_int(va_arg(args, unsigned int), i, fd);
	else if (format[j] == 'x')
		i = print_hex(va_arg(args, int), i, 1, fd);
	else if (format[j] == 'X')
		i = print_hex(va_arg(args, int), i, 2, fd);
	else if (format[j] == '%')
		i = ft_putchar('%', i, fd);
	if (i == -1)
		return (-1);
	return (i);
}
