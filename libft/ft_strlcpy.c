/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:21:22 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 21:58:00 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_STRLCPY:							   *
*	La función ft_strlcpy copia una cadena de origen (src) en  *
*	una cadena de destino (dst) con un límite de tamaño        *
*	especificado (size). Devuelve la longitud de la cadena     *
*	de origen (src) que intentó copiar.                        *
*															   *	
*	Argumentos:												   *
*	dst: La cadena de destino donde se copiará src.            *
*	src: La cadena de origen que se copiará en dst.            *
*	size: El tamaño máximo de dst, incluyendo el carácter      *
*	nulo de terminación.                                       *
*															   *
\**************************************************************/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
    char destino[20];
    char fuente[] = "Hola, mundo!";
    size_t limite = 20;

    size_t resultado_ft_strlcpy = ft_strlcpy(destino, fuente, limite);
    //size_t resultado_strlcpy = strlcpy(destino, fuente, limite);

    printf("Resultado ft_strlcpy: %zu\n", resultado_ft_strlcpy);
    printf("Cadena de destino: %s\n", destino);

    //printf("Resultado strlcpy: %zu\n", resultado_strlcpy);
   // printf("Cadena de destino: %s\n", destino);

    return 0;
}*/
