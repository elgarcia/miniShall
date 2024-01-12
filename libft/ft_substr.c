/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:16:38 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 12:13:43 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_SUBSTR:							   *
*	La función ft_substr crea una nueva cadena de caracteres   *
*	a partir de una cadena existente `s`. La nueva cadena      *
*	empieza en la posición `start` y tiene una longitud de     *
*	hasta `len` caracteres. Devuelve un puntero a la nueva     *
*	cadena o NULL si hay un error de asignación de memoria.    *
*															   *	
*	Argumentos:												   *
*	s: La cadena de caracteres de la que se creará la nueva    *
*	cadena.													   *
*	start: La posición desde la cual comenzar la nueva cadena. *
*	len: La longitud máxima de la nueva cadena.                *
*															   *
*	Devuelve: Un puntero a la nueva cadena de caracteres o     *
*	NULL si hay un error.									   *
*															   *
\**************************************************************/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, (s + start), len + 1);
	return (new);
}
/*
#include <stdio.h>
int main()
{
    char *cadena = "Hola como estas";
    unsigned int inicio = 5;
    size_t longitud = 5;

    char *resultado_ft_substr = ft_substr(cadena, inicio, longitud);
	printf("Cadena: %s\nInicio: %d\nLongitud: %ld\n", cadena,inicio,longitud);
    printf("Resultado ft_substr: \"%s\"\n", resultado_ft_substr);

    free(resultado_ft_substr);
    return 0;
}*/
