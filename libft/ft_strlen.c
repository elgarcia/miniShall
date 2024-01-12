/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:56:08 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 21:59:47 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_STRLEN:							  *
*	La función ft_strlen calcula la longitud de una cadena de *
*	caracteres (str), es decir, el número de caracteres hasta *
*	el carácter nulo de terminación ('\0').                   *
*															  *	
*	Argumentos:												  *
*	str: La cadena de caracteres cuya longitud se calculará.  *
*															  *
\*************************************************************/

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <string.h>
int main() {
    char *cadena = "Hola, mundo!";

    size_t resultado_ft_strlen = ft_strlen(cadena);
    size_t resultado_strlen = strlen(cadena);
	printf("Cadena: %s\n", cadena);
    printf("Resultado ft_strlen: %zu\n", resultado_ft_strlen);
    printf("Resultado strlen: %zu\n", resultado_strlen);

    return 0;
}*/
