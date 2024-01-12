/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:03:00 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 09:39:20 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*					FT_CALLOC:
	Asigna memoria para un número especificado de elementos
	de un tamaño dado, y la inicializa a cero.
	Es útil para asignar y preparar memoria para estructuras
	de datos, como arreglos.
*/
void	*ft_calloc(size_t num_elements, size_t size)
{
	void	*result;

	result = malloc(num_elements * size);
	if (!result)
		return (NULL);
	else
	{
		ft_bzero(result, num_elements * size);
		return (result);
	}
}
/*
#include <stdio.h>
int main()
{
    size_t num_elements = 5;
    size_t element_size = sizeof(int);
    char *arr;

    arr = (char *)ft_calloc(num_elements, element_size);

    if (arr == NULL) {
        printf("La asignación de memoria ha fallado.\n");
        return 1;
    }
    for (size_t i = 0; i < num_elements; i++) {
        arr[i] = i * 2;
		printf("%d ", arr[i]);
    }
    // Libera la memoria asignada
    free(arr);

    return 0;
}*/
