/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:24:17 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 22:14:51 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_STRNCMP:							   *
*	La función ft_strncmp compara los primeros n caracteres    *
*	de dos cadenas de caracteres (s1 y s2). Devuelve un valor  *
*	entero menor que, igual a, o mayor que cero según si s1    *
*	es menor que, igual a, o mayor que s2, respectivamente.    *
*															   *	
*	Argumentos:												   *
*	s1: La primera cadena de caracteres que se comparará.      *
*	s2: La segunda cadena de caracteres que se comparará.      *
*	n: El número de caracteres a comparar.                     *
*															   *
\**************************************************************/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	}
	return (0);
}
/*
#include <stdio.h>
int main()
{
    char *cadena1 = "Hola, mundo!";
    char *cadena2 = "Hola, amigos!";
    size_t longitud = 5;

	printf("Cadena 1: %s\nCadena 2: %s\n", cadena1, cadena2);
	printf("Longitud a comparar %ld\n", longitud);
    int resultado_ft_strncmp = ft_strncmp(cadena1, cadena2, longitud);
    int resultado_strncmp = strncmp(cadena1, cadena2, longitud);

    printf("Resultado ft_strncmp: %d\n", resultado_ft_strncmp);
    printf("Resultado strncmp: %d\n", resultado_strncmp);

    if (resultado_ft_strncmp < 0) {
        printf("La cadena 1 es menor que la cadena 2.\n");
    } else if (resultado_ft_strncmp == 0) {
        printf("Las cadenas son iguales.\n");
    } else {
        printf("La cadena 1 es mayor que la cadena 2.\n");
    }

    return 0;
}*/
