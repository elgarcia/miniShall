/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:54:49 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 20:40:57 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_ISPRINT:							  *
*	La función ft_isprint se utiliza para determinar si      *
*	un valor de tipo int representa un carácter imprimible   *
*	de acuerdo con la tabla ASCII extendida (códigos de      *
*	carácter de 32 a 126). Devuelve 1 si el valor es un     *
*	carácter imprimible y 0 si no lo es.				      *
*															  *	
*	Argumentos:												  *
*	c: Un valor de tipo int que representa un carácter o	  *
*	código de carácter ASCII.								  *
*															  *
\*************************************************************/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
#include <stdio.h>
int main() {
    int values[] = {31, 32, 65, 97, 126, 127, 160};
    int num_values = sizeof(values) / sizeof(values[0]);

    printf("Valores y resultado de ft_isprint:\n");

    for (int i = 0; i < num_values; i++) {
        int result = ft_isprint(values[i]);
        if (result) {
            printf("%d -> Es un carácter imprimible\n", values[i]);
        } else {
            printf("%d -> No es un carácter imprimible\n", values[i]);
        }
    }

    return 0;
}*/
