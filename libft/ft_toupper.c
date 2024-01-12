/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:15:36 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 22:34:46 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_TOUPPER:							  *
*	La función ft_toupper convierte un carácter en minúscula  *
*	a su equivalente en mayúscula si es una letra minúscula.  *
*	De lo contrario, devuelve el mismo carácter.              *
*															  *	
*	Argumentos:												  *
*	c: El carácter que se convertirá a mayúscula si es una    *
*	   letra minúscula.										  *
*															  *
*	Devuelve: El carácter convertido a mayúscula o el mismo   *
*	carácter si no es una letra minúscula.					  *
*															  *
\*************************************************************/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
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
    printf("Resultado ft_upper mayúscula: %c\n", ft_toupper(upper));
    printf("Resultado ft_upper minúscula: %c\n", ft_toupper(lower));
    return (0);
}*/
