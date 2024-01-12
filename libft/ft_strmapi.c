/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:49:10 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 22:08:57 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_STRMAPI:							  *
*	La función ft_strmapi aplica una función (f) a cada       *
*	carácter de una cadena de caracteres (s) y crea una       *
*	nueva cadena con los resultados. Devuelve un puntero a    *
*	la nueva cadena o NULL en caso de error de asignación     *
*	de memoria.                                               *
*															  *	
*	Argumentos:												  *
*	s: La cadena de caracteres en la que se aplicará la       *
*	función.												  *
*	f: La función que se aplicará a cada carácter, tomando    *
*	la posición del carácter como primer argumento y el       *
*	carácter como segundo argumento.                          *
*															  *
\*************************************************************/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!s || !f || !str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
char to_mayus(unsigned int posicion, char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return (c);
}

int main()
{
    char *cadena = "Hola, mundo!";
    char *resultado_ft_strmapi = ft_strmapi(cadena, to_mayus);

	printf("Cadena: %s\n", cadena);
    printf("Resultado ft_strmapi: %s\n", resultado_ft_strmapi);
    free(resultado_ft_strmapi);
    return 0;
}*/
