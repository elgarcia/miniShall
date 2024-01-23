/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:27:38 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 22:49:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_fprintf(int fd, char const *format, ...)
{
	int		i;
	int		j;
	va_list	args;

	i = 0;
	j = -1;
	va_start(args, format);
	while (format[++j])
	{
		if (format[j] == '%')
		{
			j++;
			if (ft_strchr("cspdiuxX%", format[j]))
				i = check_format(args, format, i, j, fd);
		}
		else
			i = ft_putchar(format[j], i, fd);
		if (i == -1)
			return (-1);
	}
	va_end(args);
	return (i);
}
