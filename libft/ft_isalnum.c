/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:46:19 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 09:40:09 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*						FT_ISALNUM:
 * Determina si un carácter es alfanumérico, es decir,
 * si es una letra (mayúscula o minúscula) o un dígito,
 * y devuelve 1 si es alfanumérico y 0 si no lo es.
*/
int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= 48 && c <= 57));
}
/*
#include <stdio.h>
int main() {
    char characters[] = {'a', '5', '$', 'Z', '9', '!', 'B'};
    int num_characters = sizeof(characters) / sizeof(characters[0]);

    printf("Caracteres y resultado de ft_isalnum:\n");

    for (int i = 0; i < num_characters; i++) {
        int result = ft_isalnum(characters[i]);
        if (result) {
            printf("%c -> Es alfanumérico\n", characters[i]);
        } else {
            printf("%c -> No es alfanumérico\n", characters[i]);
        }
    }

    return 0;
}*/
