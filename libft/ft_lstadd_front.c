/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:12:30 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 09:52:01 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************
*						FT_LSTADD_FRONT:					  *
*	La función ft_lstadd_front agrega un nuevo nodo `new` al  *
*	principio de una lista enlazada representada por un       *
*	puntero a puntero `lst`. Si la lista está vacía, el       *
*	puntero `lst` se actualizará para apuntar al nuevo nodo.  *
*	Si la lista no está vacía, el nuevo nodo se enlazará con  *
*	el nodo inicial existente y luego se actualizará el       *
*	puntero `lst` para apuntar al nuevo nodo.				  *
*															  *
*	Argumentos:												  *
*	lst: Un puntero a puntero que apunta al puntero inicial   *
*	     de la lista enlazada.								  *
*	new: Un puntero al nuevo nodo que se agregará al inicio   *
*	     de la lista.										  *
*															  *
*	Devuelve: Nada (void).									  *
*															  *
\*************************************************************/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
#include <stdio.h>
int main(void)
{
    t_list *lista = NULL;

    t_list *elemento1 = ft_lstnew("Elemento 1");
    t_list *elemento2 = ft_lstnew("Elemento 2");
    t_list *elemento3 = ft_lstnew("Elemento 3");

    ft_lstadd_front(&lista, elemento3);
    ft_lstadd_front(&lista, elemento2);
    ft_lstadd_front(&lista, elemento1);

    t_list *current = lista;
    while (current)
	{
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

    free(elemento1);
    free(elemento2);
    free(elemento3);

    return 0;
}*/
