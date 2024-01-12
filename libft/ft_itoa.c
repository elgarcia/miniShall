/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:48:45 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 17:34:29 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_ITOA:							   *
*	La función ft_itoa convierte un número entero en su        *
*	representación como una cadena de caracteres.              *
*															   *	
*	Argumentos:												   *
*	n: El número entero que se convertirá en una cadena de     *
*	   caracteres.											   *
*															   *
*	Devuelve: Un puntero a la cadena de caracteres que         *
*	representa el número, o NULL si hay un error de asignación *
*	de memoria.												   *
*															   *
\**************************************************************/

static int	len_num(int n, int counter)
{
	if (n > -2147483648 && n < 0)
		return (len_num(-n, counter + 1));
	else if (n > 0)
		return (len_num(n / 10, counter + 1));
	else
		return (counter);
}

static char	*to_string(int n, int len)
{
	char	*str;
	size_t	i;
	int		nb;

	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
		i++;
	}
	while (n > 0)
	{
		nb = n % 10;
		str[--len] = nb + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int	len;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n < -2147483647)
		return (ft_strdup("-2147483648"));
	else if (n > 2147483647)
		return (ft_strdup("2147483647"));
	len = len_num(n, 0);
	return (to_string(n, len));
}
/*
#include <stdio.h>
int main()
{
    int numero1 = 23455;
    int numero2 = -6789;
    int numero3 = 0;

    char *resultado_ft_itoa1 = ft_itoa(numero1);
    char *resultado_ft_itoa2 = ft_itoa(numero2);
    char *resultado_ft_itoa3 = ft_itoa(numero3);
	printf("Numero entero 1: %d\n", numero1);
    printf("Numero entero 2: %d\n", numero2);
    printf("Numero entero 3: %d\n", numero3);

    printf("Resultado ft_itoa1: \"%s\"\n", resultado_ft_itoa1);
    printf("Resultado ft_itoa2: \"%s\"\n", resultado_ft_itoa2);
    printf("Resultado ft_itoa3: \"%s\"\n", resultado_ft_itoa3);

    free(resultado_ft_itoa1);  
	free(resultado_ft_itoa2);
    free(resultado_ft_itoa3);

    return 0;
}*/
