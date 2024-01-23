/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:40:56 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/26 17:26:44 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include <stdio.h>
int	main(void)
{
	char *str = "Hello, World!";
    int num = 42;
    char ch = 'A';
    void *ptr = (void *)&num;
    unsigned int hex = 0x1A3F;
    unsigned int HEX = 0x1A3F;

    // Prueba de cada flag
	ft_printf("\n----------------------------------------------\n\n");
    ft_printf("\nFlag 'c':\n\n");
    ft_printf("ft_printf: %c\n", ch);
    printf("printf:    %c\n", ch);
	ft_printf("\n----------------------------------------------\n\n");

    ft_printf("\nFlag 's':\n\n");
    ft_printf("ft_printf: %s\n", str);
    printf("printf:    %s\n", str);
	ft_printf("\n----------------------------------------------\n\n");

    ft_printf("\nFlag 'p':\n\n");
    ft_printf("ft_printf: %p\n", ptr);
    printf("printf:    %p\n", ptr);
	ft_printf("\n----------------------------------------------\n\n");

    ft_printf("\nFlag 'd':\n\n");
    ft_printf("ft_printf: %d\n", num);
    printf("printf:    %d\n", num);
	ft_printf("\n----------------------------------------------\n\n");

    ft_printf("\nFlag 'i':\n\n");
    ft_printf("ft_printf: %i\n", num);
    printf("printf:    %i\n", num);
	ft_printf("\n----------------------------------------------\n\n");

    ft_printf("\nFlag 'u':\n\n");
    ft_printf("ft_printf: %u\n", num);
    printf("printf:    %u\n", num);
	ft_printf("\n----------------------------------------------\n\n");

    ft_printf("\nFlag 'x':\n\n");
    ft_printf("ft_printf: %x\n", hex);
    printf("printf:    %x\n", hex);
	ft_printf("\n----------------------------------------------\n\n");

    ft_printf("\nFlag 'X':\n\n");
    ft_printf("ft_printf: %X\n", HEX);
    printf("printf:    %X\n", HEX);
	ft_printf("\n----------------------------------------------\n\n");

	ft_printf("\ncomprobacion de %%u\n");
	ft_printf("ft_printf: %u\n", -10);
	printf("printf:    %u\n", -10);
	ft_printf("\n----------------------------------------------\n\n");

	ft_printf("%%p vacio\n");
	ft_printf("ft_printf: %p\n", "");
	printf("printf:    %p\n", "");
	ft_printf("\n----------------------------------------------\n\n");
	
	ft_printf("%p %u %d %i %s\n", "", 2342342, 90234, -12432, "");
	printf("%p %u %d %i %s\n", "", 2342342, 90234, -12432, "");

    return (0);
}
