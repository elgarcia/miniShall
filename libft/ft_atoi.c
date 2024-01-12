/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:47:14 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 09:29:08 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*						FT_ATOI: 
 Convierte una cadena de caracteres en un número entero,
 teniendo en cuenta los signos (+/-) y los dígitos numéricos en la cadena.
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
/*
#include <stdio.h>
int main()
{
    // Casos de prueba
    const char *test_cases[] = {
        "12345",
        "-6789",
        "0",
        "  42",
        "   +99",
        "  -123abc",
        "  2147483647",
        "  -2147483648",
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int result = ft_atoi(test_cases[i]);
        printf("Cadena: \"%s\" -> Resultado: %d\n", test_cases[i], result);
    }

    return 0;
}*/
