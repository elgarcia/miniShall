/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:55:06 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 10:06:26 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_MEMCMP:							  *
*	La función ft_memcmp compara los primeros n bytes de dos  *
*	bloques de memoria (s1 y s2). Devuelve un valor menor,    *
*	mayor o igual a cero según si s1 es menor, mayor o igual  *
*	que s2.													  *	
*															  *	
*	Argumentos:												  *
*	s1: Un puntero al primer bloque de memoria a comparar.    *
*	s2: Un puntero al segundo bloque de memoria a comparar.   *
*	n: El número de bytes que se compararán entre los dos     *
*	bloques de memoria.									      *
*															  *
\*************************************************************/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if ((str1[i] != str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int main() {
    char s1[] = "hola";
    char s2[] = "holo";
    size_t n = 4;

	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
    int resultado_ft = ft_memcmp(s1, s2, n);
    int resultado_original = memcmp(s1, s2, n);

    printf("Resultado (ft_memcmp): %d\n", resultado_ft);
    printf("Resultado (memcmp): %d\n", resultado_original);

    return 0;
}*/
