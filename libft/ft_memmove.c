/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:56:39 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 16:05:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_MEMMOVE:							  *
*	La función ft_memmove copia len bytes de una zona de      *
*	memoria origen (src) a una zona de memoria destino (dst), *
*	posiblemente solapándose. Devuelve un puntero a la zona   *
*	de memoria destino.                                       *	
*															  *	
*	Argumentos:												  *
*	dst: Un puntero a la zona de memoria destino donde se     *
*	realizará la copia.										  *
*	src: Un puntero a la zona de memoria origen desde donde   *
*	se copiarán los datos.									  *
*	len: El número de bytes que se copiarán desde src a dst.  *
*															  *
\*************************************************************/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*srce;
	char	*dest;
	size_t	i;

	i = len;
	srce = (char *)src;
	dest = (char *)dst;
	if (srce == dest)
		return (dest);
	if (srce < dest)
	{
		while (i-- > 0)
			dest[i] = srce[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			dest[i] = srce[i];
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
    char str[] = "Hola, mundo!";
    char dest[20];
    size_t n = strlen(str) + 1;
	printf("Antes de copiar las cadenas:\n");
	printf("str = %s\n", str);
	printf("dest = %s\n\n", dest);
    void *resultado_ft_memmove = ft_memmove(dest, str, n);
    void *resultado_memmove = memmove(dest, str, n);

    printf("Copia de cadenas de caracteres:\n");
    printf("Resultado ft_memmove: %s\n", (char *)resultado_ft_memmove);
    printf("Resultado memmove: %s\n", (char *)resultado_memmove);

    int arr[] = {1, 2, 3, 4, 5};
    int dest_arr[5];
    size_t tamano_arreglo = sizeof(arr);

    resultado_ft_memmove = ft_memmove(dest_arr, arr, tamano_arreglo);
    resultado_memmove = memmove(dest_arr, arr, tamano_arreglo);

    printf("\nCopia de arreglos de enteros:\n");
    printf("Resultado ft_memmove: [");
    for (int i = 0; i < 5; i++) {
        printf("%d", dest_arr[i]);
        if (i < 4) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Resultado memmove: [");
    for (int i = 0; i < 5; i++) {
        printf("%d", ((int *)resultado_memmove)[i]);
        if (i < 4) {
            printf(", ");
        }
    }
    printf("]\n");

    return (0);
}*/
