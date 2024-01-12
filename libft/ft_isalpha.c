/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:24:07 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 09:40:48 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**********************************************************	
*						 FT_ISALPHA:					  *
*	La función ft_isalpha se utiliza para determinar	  *
*	si un carácter es una letra del alfabeto. Devuelve 1  *
*	si el carácter es una letra (mayúscula o minúscula)   *
*	y 0 si no lo es.									  *	
*														  *	
*	Argumentos:											  *
*	c: Un valor de tipo int que representa un carácter,	  *
*	generalmente en forma de su valor ASCII.			  * 
*														  *
\*********************************************************/

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/*
#include <stdio.h>
int main() {
    char characters[] = {'a', '5', 'B', '$', 'z', '!', 'C'};
    int num_characters = sizeof(characters) / sizeof(characters[0]);

    printf("Caracteres y resultado de ft_isalpha:\n");

    for (int i = 0; i < num_characters; i++) {
        int result = ft_isalpha(characters[i]);
        if (result) {
            printf("%c -> Es una letra\n", characters[i]);
        } else {
            printf("%c -> No es una letra\n", characters[i]);
        }
    }

    return 0;
}*/
