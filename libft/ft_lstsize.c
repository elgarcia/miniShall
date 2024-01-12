/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:12:56 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 10:39:41 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*****************************************************************	
*						FT_LSTSIZE:								 *
*	La función ft_lstsize cuenta el número de elementos en una   *
*	lista enlazada. Recorre la lista desde el primer nodo hasta  *
*	el último, incrementando un contador en cada paso. Devuelve  *
*	el número total de elementos en la lista.					 *
*															     * 	
*	Argumentos:												     *
*	lst: Un puntero al primer nodo de la lista enlazada.         *
*															     *
*	Devuelve: El número de elementos en la lista enlazada.       *
*															     *
\****************************************************************/

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*actual;

	if (!lst)
		return (0);
	counter = 0;
	actual = lst;
	while (actual)
	{
		counter++;
		actual = actual->next;
	}
	return (counter);
}
/*
#include <stdio.h>
void del(void *content)
{
    free(content);
}

int	main(void)
{
    t_list *lista = NULL;
    t_list *elemento1 = ft_lstnew(strdup("Elemento 1"));
    t_list *elemento2 = ft_lstnew(strdup("Elemento 2"));
    t_list *elemento3 = ft_lstnew(strdup("Elemento 3"));

    ft_lstadd_back(&lista, elemento1);
    ft_lstadd_back(&lista, elemento2);
    ft_lstadd_back(&lista, elemento3);

    int numero_de_elementos = ft_lstsize(lista);

    printf("Número de elementos en la lista: %d\n", numero_de_elementos);

    ft_lstclear(&lista, del);
    return 0;
}*/
