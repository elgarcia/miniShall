/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:40:19 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/18 16:47:46 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*******************************************************************	
*						FT_STRTRIM:								   *
*	La función ft_strtrim elimina los caracteres especificados	   *
*	por el conjunto `set` al principio y al final de una cadena	   *
*	de caracteres `s1`. Devuelve una nueva cadena de caracteres	   *
*	con los caracteres eliminados.                                 *
*																   *	
*	Argumentos:													   *
*	s1: La cadena de caracteres de la que se eliminarán los		   *
*	caracteres del conjunto `set`.                                 *
*	set: El conjunto de caracteres que se eliminarán de `s1`.      *
*															       *
*	Devuelve: Un puntero a la nueva cadena de caracteres           *
*	resultante, o NULL si hay un error de asignación de memoria.   *
*															       *
\******************************************************************/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	j;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	j = ft_strlen(s1);
	while (j && ft_strchr(set, s1[j]))
		j--;
	str = ft_substr(s1, 0, j + 1);
	if (!str)
		return (NULL);
	return (str);
}
/*
#include <stdio.h>
int main() {
    char *cadena = "  Hola  ";
    char *conjunto = " ";
    char *resultado_ft_strtrim = ft_strtrim(cadena, conjunto);
	
	printf("Cadena sin limpiar: <%s>\n", cadena);
    printf("Resultado ft_strtrim: <%s>\n", resultado_ft_strtrim);
    free(resultado_ft_strtrim);
	return 0;
}*/
