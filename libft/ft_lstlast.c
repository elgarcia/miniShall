/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:41:50 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 10:19:51 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_LSTLAST:							  *
*	La función ft_lstlast devuelve un puntero al último nodo  *
*	de una lista enlazada representada por el puntero `lst`.  *
*	Si la lista está vacía (es decir, `lst` es NULL), la      *
*	función devuelve NULL.									  *
*															  *	
*	Argumentos:												  *
*	lst: Un puntero al primer nodo de la lista enlazada.      *
*															  *
*	Devuelve: Un puntero al último nodo de la lista o NULL si *
*	la lista está vacía.									  *
*															  *
\*************************************************************/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}
/*
#include <stdio.h>
int	main(void)
{
    t_list *lista = NULL;
    t_list *elemento1 = ft_lstnew(strdup("Elemento 1"));
    t_list *elemento2 = ft_lstnew(strdup("Elemento 2"));
    t_list *elemento3 = ft_lstnew(strdup("Elemento 3"));

    ft_lstadd_back(&lista, elemento1);
    ft_lstadd_back(&lista, elemento2);
    ft_lstadd_back(&lista, elemento3);

    t_list *ultimo_nodo = ft_lstlast(lista);
    if (ultimo_nodo)
        printf("Contenido del último nodo: %s\n", (char *)ultimo_nodo->content);
	else
        printf("La lista está vacía.\n");

    return 0;
}*/
