/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:57:18 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 10:43:34 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_MEMSET:							  *
*	La función ft_memset establece los primeros len bytes     *
*	de una zona de memoria (b) con un valor específico (c).   *
*	Devuelve un puntero a la zona de memoria modificada.      *	
*															  *	
*	Argumentos:												  *
*	b: Un puntero a la zona de memoria donde se realizará     *
*	la operación de establecimiento de valores.               *
*	c: El valor que se establecerá en los bytes de memoria.   *
*	len: El número de bytes que se establecerán con el valor  *
*	específico.												  *
*															  *
\*************************************************************/

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)b;
	while (len--)
		*tmp++ = (unsigned char)c;
	return (b);
}
/*
#include <stdio.h>
int main()
{
    char str[20];
    int valor = 'A';
    size_t n = 10;
	char str2[20];

    printf("Antes (ft_memset): %s\n", str);
    ft_memset(str, valor, n);
    printf("Después (ft_memset): %s\n", str);
	
    printf("\nAntes (memset): %s\n", str2);
    memset(str2, valor, n);
    printf("Después (memset): %s\n", str2);

    return 0;
}*/
