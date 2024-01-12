/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:00:18 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 09:56:21 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************
*						FT_LSTCLEAR:						   *
*	La función ft_lstclear elimina y libera la memoria de      *
*	todos los nodos de una lista enlazada representada por un  *
*	puntero a puntero `lst`. También toma como argumento una   *
*	función `del` que se utiliza para liberar la memoria del   *
*	contenido de cada nodo.									   *
*															   *
*	Argumentos:												   *
*	lst: Un puntero a puntero que apunta al puntero inicial    *
*	     de la lista enlazada.								   *
*	del: Una función que toma un puntero al contenido de un    *
*	     nodo y libera la memoria asociada a ese contenido.	   *
*															   *
*	Devuelve: Nada (void).									   *
*															   *
\**************************************************************/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	else
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}
/*
#include <stdio.h>
void del(void *content) {
    free(content);
}

int main()
{
    t_list *lista = NULL;
    t_list *elemento1 = ft_lstnew(strdup("Elemento 1"));
    t_list *elemento2 = ft_lstnew(strdup("Elemento 2"));
    t_list *elemento3 = ft_lstnew(strdup("Elemento 3"));

    lista = elemento1;
    elemento1->next = elemento2;
    elemento2->next = elemento3;

    t_list *current = lista;
    while (current) {
        printf("Elemento: %s\n", (char *)current->content);
        current = current->next;
    }

    ft_lstclear(&lista, del);

    if (lista == NULL) {
        printf("La lista se ha eliminado y está vacía.\n");
    }

    return 0;
}*/
