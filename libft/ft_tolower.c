/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:21:46 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 22:32:44 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_TOLOWER:							   *
*	La función ft_tolower convierte un carácter en mayúscula   *
*	a su equivalente en minúscula si es una letra mayúscula.   *
*	De lo contrario, devuelve el mismo carácter.               *
*															   *	
*	Argumentos:												   *
*	c: El carácter que se convertirá a minúscula si es una     *
*	   letra mayúscula.										   *
*															   *
*	Devuelve: El carácter convertido a minúscula o el mismo    *
*	carácter si no es una letra mayúscula.					   *
*															   *
\**************************************************************/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c += 32);
	return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	char	upper;
    char	lower;

	upper = 'H';
	lower = 'h';
	printf("Caracter mayuscula antes de la funcion: %c\n", upper);
	printf("Caracter minuscula antes de la funcion: %c\n", lower);
    printf("Resultado ft_tolower mayúscula: %c\n", ft_tolower(upper));
    printf("Resultado ft_tolower minúscula: %c\n", ft_tolower(lower));
    return (0);
}*/
