/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:31:25 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/15 10:13:56 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	check_format(va_list args, const char *format, t_fprintf fprintf, int fd)
{
	if (format[fprintf.j] == 'c')
		fprintf.i = ft_putchar(va_arg(args, int), fprintf.i, fd);
	else if (format[fprintf.j] == 's')
		fprintf.i = print_str(va_arg(args, char *), fprintf.i, fd);
	else if (format[fprintf.j] == 'p')
		fprintf.i = print_address(va_arg(args, void *), fprintf.i, fd);
	else if (format[fprintf.j] == 'd')
		fprintf.i = ft_putnbr(va_arg(args, int), fprintf.i, fd);
	else if (format[fprintf.j] == 'i')
		fprintf.i = ft_putnbr(va_arg(args, int), fprintf.i, fd);
	else if (format[fprintf.j] == 'u')
		fprintf.i = unsigned_int(va_arg(args, unsigned int), fprintf.i, fd);
	else if (format[fprintf.j] == 'x')
		fprintf.i = print_hex(va_arg(args, int), fprintf.i, 1, fd);
	else if (format[fprintf.j] == 'X')
		fprintf.i = print_hex(va_arg(args, int), fprintf.i, 2, fd);
	else if (format[fprintf.j] == '%')
		fprintf.i = ft_putchar('%', fprintf.i, fd);
	if (fprintf.i == -1)
		return (-1);
	return (fprintf.i);
}
