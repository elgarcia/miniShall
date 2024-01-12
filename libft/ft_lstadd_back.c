/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:48:52 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 09:42:19 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_LSTADD_BACK:						   *
*	La función ft_lstadd_back agrega un nuevo elemento `new`   *
*	al final de una lista enlazada representada por un puntero *
*	a puntero `lst`. Si la lista está vacía, el puntero `lst`  *
*	se actualizará para apuntar al nuevo elemento. Si la lista *
*	no está vacía, el nuevo elemento se agregará al final de   *
*	la lista existente.										   *
*															   *	
*	Argumentos:												   *
*	lst: Un puntero a puntero que apunta al puntero inicial    *
*	     de la lista enlazada.								   *
*	new: Un puntero al nuevo elemento que se agregará a la     *
*	     lista.												   *
*															   *
*	Devuelve: Nada (void).									   *
*															   *
\**************************************************************/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
/*
#include <stdio.h>
int	main(void)
{
    t_list *lista = NULL;

    t_list *elemento1 = ft_lstnew("Elemento 1");
    t_list *elemento2 = ft_lstnew("Elemento 2");
    t_list *elemento3 = ft_lstnew("Elemento 3");

    ft_lstadd_back(&lista, elemento1);
    ft_lstadd_back(&lista, elemento2);

    ft_lstadd_back(&lista, elemento3);

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
