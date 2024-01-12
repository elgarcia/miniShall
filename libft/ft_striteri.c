/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:05:57 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 11:39:38 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_STRITERI:						  *
*	La función ft_striteri aplica una función (f) a cada      *
*	carácter de una cadena de caracteres (s), pasando la      *
*	posición del carácter como primer argumento.              *
*															  *	
*	Argumentos:												  *
*	s: La cadena de caracteres en la que se aplicará la       *
*	función.												  *
*	f: La función que se aplicará a cada carácter, tomando    *
*	la posición del carácter como primer argumento y el       *
*	puntero al carácter como segundo argumento.               *
*															  *
\*************************************************************/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
void	imprimir_posicion_caracter(unsigned int posicion, char *caracter)
{
	printf("Posición: %u, Carácter: %c\n", posicion, *caracter);
}

int main()
{
    char *cadena = "Hola!";

    printf("Cadena original: %s\n", cadena);
    ft_striteri(cadena, imprimir_posicion_caracter);
    return 0;
}*/
