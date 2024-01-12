/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:44:01 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 20:39:11 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_ISDIGIT:							  *
*	La función ft_isdigit se utiliza para determinar si       *
*	un carácter representa un dígito decimal. Devuelve 1      *
*	si el carácter es un dígito (0-9) y 0 si no lo es.		  *
*															  *	
*	Argumentos:												  *
*	c: Un valor de tipo int que representa un carácter.		  *
*															  *
\*************************************************************/

int	ft_isdigit(int c)
{
	return ((c >= 48) && (c <= 57));
}
/*
#include <stdio.h>
int main() {
    char characters[] = {'a', '5', '9', '$', '0', '!', '7'};
    int num_characters = sizeof(characters) / sizeof(characters[0]);

    printf("Caracteres y resultado de ft_isdigit:\n");

    for (int i = 0; i < num_characters; i++) {
        int result = ft_isdigit(characters[i]);
        if (result) {
            printf("%c -> Es un dígito\n", characters[i]);
        } else {
            printf("%c -> No es un dígito\n", characters[i]);
        }
    }

    return 0;
}*/
