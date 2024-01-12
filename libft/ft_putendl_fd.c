/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:22:27 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 21:18:27 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/****************************************************************	
*						FT_PUTENDL_FD:						    *
*	La función ft_putendl_fd escribe una cadena de caracteres   *
*	(s) seguida de un salto de línea en el descriptor de        *
*	archivo especificado (fd).                                  *	
*															    *	
*	Argumentos:												    *
*	s: La cadena de caracteres que se escribirá en el           *
*	descriptor de archivo.                                      *
*	fd: El descriptor de archivo donde se escribirá la cadena   *
*	de caracteres y el salto de línea.                          *
*															    *
\***************************************************************/

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	write(fd, "\n", 1);
}
/*
int main()
{
    char *cadena = "Hola, mundo!";
    int descriptor_de_archivo = 1;  
	// 1 corresponde a la salida estándar (stdout)

    ft_putendl_fd(cadena, descriptor_de_archivo);

    return 0;
}*/
