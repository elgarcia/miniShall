/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:15:59 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 21:23:52 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_PUTSTR_FD:						   *
*	La función ft_putstr_fd escribe una cadena de caracteres   *
*	(s) en el descriptor de archivo especificado (fd).         *	
*															   *	
*	Argumentos:												   *
*	s: La cadena de caracteres que se escribirá en el          *
*	descriptor de archivo.                                     *
*	fd: El descriptor de archivo donde se escribirá la cadena  *
*	de caracteres.                                             *
*															   *
\**************************************************************/

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
/*
int main()
{
    char *cadena = "Hola, mundo!";
    int descriptor_de_archivo = 1;  
// 1 corresponde a la salida estándar (stdout)

    ft_putstr_fd(cadena, descriptor_de_archivo);

    return 0;
}*/
