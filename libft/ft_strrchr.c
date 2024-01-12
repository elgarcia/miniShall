/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:47:35 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/17 22:18:56 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_STRRCHR:							  *
*	La función ft_strrchr busca la última aparición de un     *
*	carácter (c) en una cadena de caracteres (s). Devuelve    *
*	un puntero al carácter encontrado o NULL si no se         *
*	encuentra.                                                *
*															  *	
*	Argumentos:												  *
*	s: La cadena de caracteres en la que se buscará el        *
*	carácter.												  *
*	c: El carácter que se buscará en la cadena.               *
*															  *
\*************************************************************/

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	l;

	str = NULL;
	l = (char)c;
	while (*s)
	{
		if (*s == l)
			str = (char *)s;
		s++;
	}
	if (*s == l)
		str = (char *)s;
	return (str);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
  char *str = "hola como estas";
  int c = 'h';
  printf("%s\n", strrchr(str,c));
  printf("%s", ft_strrchr(str,c));
  return 0;
}*/
