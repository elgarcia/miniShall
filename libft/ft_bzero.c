/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:30:26 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/20 09:29:58 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*						FT_BZERO:
*	Establece todos los bytes de un bloque de memoria a cero.
*	Es útil para inicializar o "borrar" la memoria de manera eficiente.
*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include <stdio.h>
int main()
{
    char buffer[10];

    // Llena el buffer con caracteres no nulos
    ft_strlcpy(buffer, "Hello!", sizeof(buffer));

    // Muestra el contenido del buffer antes de aplicar bzero
    printf("Antes de bzero: \"%s\"\n", buffer);

    // Aplica bzero al buffer para establecer todos los bytes en cero
    ft_bzero(buffer, sizeof(buffer));

    // Muestra el contenido del buffer después de aplicar bzero
    printf("Después de bzero: \"%s\"\n", buffer);

    return 0;
}*/
