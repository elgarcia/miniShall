/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:51:12 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 20:37:45 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						  FT_ISASCII:						  *
*	La función ft_isascii se utiliza para determinar		  *
*	si un valor de tipo int representa un carácter ASCII      *
*	válido. Devuelve 1 si el valor está en el rango 0-127     *
*	(inclusive), que es el rango de los caracteres ASCII,     *
*	y 0 en caso contrario.									  *	
*															  *	
*	Argumentos:												  *
*	c: Un valor de tipo int que se verifica como carácter	  *
*	ASCII válido.											  * 
*															  *
\*************************************************************/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
#include <stdio.h>
int main()
{
    int values[] = {-5, 64, 128, 65, 97, 0, 127};
    int num_values = sizeof(values) / sizeof(values[0]);

    printf("Valores y resultado de ft_isascii:\n");

    for (int i = 0; i < num_values; i++) {
        int result = ft_isascii(values[i]);
        if (result) {
            printf("%d -> Es un carácter ASCII válido\n", values[i]);
        } else {
            printf("%d -> No es un carácter ASCII válido\n", values[i]);
        }
    }

    return 0;
}*/
