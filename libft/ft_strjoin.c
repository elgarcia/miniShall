/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:33:05 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 21:50:29 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_STRJOIN:							  *
*	La función ft_strjoin concatena dos cadenas de caracteres *
*	(s1 y s2) en una nueva cadena de caracteres.              *
*	Devuelve un puntero a la nueva cadena concatenada o NULL  *
*	en caso de error de asignación de memoria.                *	
*															  *	
*	Argumentos:												  *
*	s1: La primera cadena de caracteres que se concatenará.   *
*	s2: La segunda cadena de caracteres que se concatenará.   *
*															  *
\*************************************************************/

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
/*
#include <stdio.h>
int main()
{
    char *cadena1 = "Hola, ";
    char *cadena2 = "mundo!";

    char *resultado_ft_strjoin = ft_strjoin(cadena1, cadena2);
	printf("Cadena 1: %s\nCadena 2: %s\n", cadena1, cadena2);
    if (resultado_ft_strjoin)
	{
        printf("Resultado: %s\n", resultado_ft_strjoin);
        free(resultado_ft_strjoin);
    }
	else
        printf("Error en ft_strjoin.\n");
    return 0;
}*/
