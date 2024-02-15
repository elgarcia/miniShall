/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:27:38 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/15 10:14:53 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fprintf(int fd, char const *format, ...)
{
	va_list		args;
	t_fprintf	fprintf;

	fprintf.i = 0;
	fprintf.j = -1;
	va_start(args, format);
	while (format[++fprintf.j])
	{
		if (format[fprintf.j] == '%')
		{
			fprintf.j++;
			if (ft_strchr("cspdiuxX%", format[fprintf.j]))
				fprintf.i = check_format(args, format, fprintf, fd);
		}
		else
			fprintf.i = ft_putchar(format[fprintf.j], fprintf.i, fd);
		if (fprintf.i == -1)
			return (-1);
	}
	va_end(args);
	return (fprintf.i);
}
