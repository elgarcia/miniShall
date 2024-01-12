/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:23:29 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 13:06:56 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_STRLCAT:							   *
*	La función ft_strlcat concatena dos cadenas de caracteres  *
*	(src y dest) en la cadena de destino (dest) con un límite  *
*	de tamaño especificado (size). Devuelve la longitud total  *
*	de la cadena resultante después de la concatenación.       *
*															   *	
*	Argumentos:												   *
*	dest: La cadena de destino donde se concatenará src.       *
*	src: La cadena de origen que se concatenará en dest.       *
*	size: El tamaño máximo de dest, incluyendo el carácter     *
*	nulo de terminación.                                       *
*															   *
\**************************************************************/

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	x;
	unsigned int	destlen;
	unsigned int	srclen;

	i = 0;
	x = ft_strlen(dest);
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	while (src[i] != '\0' && x < size - 1 && size > 0)
	{
		dest[x] = src[i];
		i++;
		x++;
	}
	dest[x] = '\0';
	if (destlen > size)
		destlen = size;
	return (destlen + srclen);
}
/*
#include <stdio.h>
int main()
{
    char destino[20] = "Hola, ";
    char fuente[] = "mundo!";
    unsigned int limite = 20;
    unsigned int resultado_ft_strlcat = ft_strlcat(destino, fuente, limite);
	printf("Fuente: %s\nDestino: %s\n", fuente, destino);
    printf("Resultado ft_strlcat: %u\n", resultado_ft_strlcat);
    printf("Cadena concatenada: %s\n", destino);
    return 0;
}*/
