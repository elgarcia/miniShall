/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:27:10 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 21:22:06 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_PUTNBR_FD:						  *
*	La función ft_putnbr_fd escribe un número entero (n) en   *
*	el descriptor de archivo especificado (fd).               *	
*															  *	
*	Argumentos:												  *
*	n: El número entero que se escribirá en el descriptor de  *
*	archivo.												  *
*	fd: El descriptor de archivo donde se escribirá el        *
*	número entero.                                            *
*															  *
\*************************************************************/

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
/*
int main() {
    int numero = 12345;
    int descriptor_de_archivo = 1; 
	// 1 corresponde a la salida estándar (stdout)

    ft_putnbr_fd(numero, descriptor_de_archivo);

    return 0;
}*/
