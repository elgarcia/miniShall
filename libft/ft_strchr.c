/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:23:15 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 10:50:50 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_STRCHR:							  *
*	La función ft_strchr busca la primera aparición de un     *
*	carácter (c) en una cadena de caracteres (s).             *
*	Devuelve un puntero al carácter encontrado o NULL si el   *
*	carácter no se encuentra en la cadena.                    *	
*															  *	
*	Argumentos:												  *
*	s: La cadena de caracteres en la que se realizará la      *
*	búsqueda.												  *
*	c: El carácter que se buscará en la cadena.               *
*															  *
\*************************************************************/

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && (char)c != *s)
		s++;
	if ((char)c == *s)
		return ((char *)s);
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int main() {
    char *cadena = "Hola, mundo!";
    char caracter = 'm';

	printf("Cadena = %s\n", cadena);
	printf("Caracter = %c\n", caracter);
    char *resultado_ft_strchr = ft_strchr(cadena, caracter);
    char *resultado_strchr = strchr(cadena, caracter);

    if (resultado_ft_strchr) {
        printf("Resultado ft_strchr: %s\n", resultado_ft_strchr);
    } else {
        printf("Carácter no encontrado en ft_strchr.\n");
    }

    if (resultado_strchr) {
        printf("Resultado strchr: %s\n", resultado_strchr);
    } else {
        printf("Carácter no encontrado en strchr.\n");
    }

    return 0;
}*/
