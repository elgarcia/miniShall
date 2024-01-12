/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:32:58 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 10:09:31 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_MEMCHR:							  *
*	La función ft_memchr busca la primera aparición de un     *
*	caracter (representado como un valor de tipo int) en      *
*	un bloque de memoria (representado por el puntero s)      *
*	de tamaño n. Si encuentra el carácter, devuelve un        *
*	puntero al lugar en la memoria donde lo encontró; si      *
*	no lo encuentra, devuelve un puntero nulo (NULL).         *
*															  *	
*	Argumentos:												  *
*	s: Un puntero a un bloque de memoria donde se realizará   *
*	la búsqueda.											  *
*	c: El valor de tipo int que se busca en el bloque de      *
*	memoria.												  *
*	n: El número de bytes en el bloque de memoria que se      *
*	analizará.											      *
*															  *
\*************************************************************/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int main()
{
    unsigned char buffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target_value = 5;
    size_t buffer_size = sizeof(buffer);
	
	printf("Numeros del array:\n");
	for (size_t i = 0; i < 9; i++)
	{
		printf("%d", buffer[i]);
		if (i < 8)
			printf(", ");
	}
	printf("\nNumero a buscar dentro del array: %d\n", target_value);
	void *result = ft_memchr(buffer, target_value, buffer_size);

    if (result)
        printf("El valor %d fue encontrado.\n", target_value);
	else
        printf("El valor %d no fue encontrado.\n", target_value);
    return 0;
}*/
