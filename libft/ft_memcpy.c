/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:42:43 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 10:10:51 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_MEMCPY:							  *
*	La función ft_memcpy copia n bytes de una zona de memoria *
*	origen (src) a una zona de memoria destino (dest).        *
*	Devuelve un puntero a la zona de memoria destino.         *	
*															  *	
*	Argumentos:												  *
*	dest: Un puntero a la zona de memoria destino donde se    *
*	realizará la copia.										  *
*	src: Un puntero a la zona de memoria origen desde donde   *
*	se copiarán los datos.									  *
*	n: El número de bytes que se copiarán desde src a dest.   *
*															  *
\*************************************************************/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src && n > 0)
		return (NULL);
	return (ft_memmove(dest, src, n));
}
/*
#include <stdio.h>
int main()
{
    // Copia de cadenas de caracteres
    char src[] = "Hola, mundo!";
    char dest[ft_strlen(src)];
    size_t n = strlen(src) + 1; 
	printf("Antes de copiar las cadenas:\n");
	printf("src = %s\n", src);
	printf("dest = %s\n\n", dest);

	void *resultado_ft_memcpy = ft_memcpy(dest, src, n);
    void *resultado_memcpy = memcpy(dest, src, n);

    printf("Copia de cadenas de caracteres:\n");
    printf("Resultado ft_memcpy: %s\n", (char *)resultado_ft_memcpy);
    printf("Resultado memcpy: %s\n", (char *)resultado_memcpy);

    // Copia de arreglos de enteros
    int src_arr[] = {1, 2, 3, 4, 5};
    int dest_arr[5];
    size_t tamano_arreglo = sizeof(src_arr);

    resultado_ft_memcpy = ft_memcpy(dest_arr, src_arr, tamano_arreglo);
    resultado_memcpy = memcpy(dest_arr, src_arr, tamano_arreglo);

    printf("\nCopia de arreglos de enteros:\n");
    printf("Resultado ft_memcpy: [");
    for (int i = 0; i < 5; i++) {
        printf("%d", dest_arr[i]);
        if (i < 4) {
            printf(", ");
        }
    }
    printf("]\n");

    printf("Resultado memcpy: [");
    for (int i = 0; i < 5; i++) {
        printf("%d", ((int *)resultado_memcpy)[i]);
        if (i < 4) {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}*/
