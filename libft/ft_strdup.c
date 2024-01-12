/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:25:37 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 10:51:43 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_STRDUP:							  *
*	La función ft_strdup duplica una cadena de caracteres     *
*	(str) en una nueva cadena de caracteres.                  *
*	Devuelve un puntero a la nueva cadena duplicada o NULL    *
*	en caso de error de asignación de memoria.                *	
*															  *	
*	Argumentos:												  *
*	str: La cadena de caracteres que se duplicará.            *
*															  *
\*************************************************************/

char	*ft_strdup(const char *str)
{
	char	*cpy;

	cpy = (char *)malloc(ft_strlen(str) + 1);
	if (!cpy)
		return (0);
	ft_memcpy(cpy, str, ft_strlen(str) + 1);
	return (cpy);
}
/*
#include <stdio.h>
int main()
{
    char *cadena = "Hola, mundo!";

    char *resultado_ft_strdup = ft_strdup(cadena);
    char *resultado_strdup = strdup(cadena);

    if (resultado_ft_strdup) {
        printf("Resultado ft_strdup: %s\n", resultado_ft_strdup);
        free(resultado_ft_strdup);
    } else {
        printf("Error en ft_strdup.\n");
    }

    if (resultado_strdup) {
        printf("Resultado strdup: %s\n", resultado_strdup);
        free(resultado_strdup);  // Liberar memoria
    } else {
        printf("Error en strdup.\n");
    }

    return 0;
}*/
