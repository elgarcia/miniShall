/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:27:05 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 22:16:59 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_STRNSTR:							   *
*	La función ft_strnstr busca una subcadena (little) dentro  *
*	de una cadena más grande (big) con un límite de longitud   *
*	especificado (len). Devuelve un puntero al comienzo de     *
*	la primera ocurrencia de little en big dentro del límite   *
*	de longitud, o NULL si no se encuentra.                    *
*															   *	
*	Argumentos:												   *
*	big: La cadena más grande en la que se buscará little.     *
*	little: La subcadena que se buscará en big.                *
*	len: El límite de longitud hasta el cual buscar.           *
*															   *
\**************************************************************/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		x;

	i = 0;
	if (*little == '\0' || !little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		x = 0;
		while (big[i + x] == little[x] && (i + x < len))
		{
			if (!little[x + 1])
				return ((char *)big + i);
			x++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 4)
		printf("%s", ft_strnstr(argv[1], argv[2], ft_atoi(argv[3])));
	return (0);
}*/
