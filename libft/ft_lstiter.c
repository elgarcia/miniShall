/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:33:53 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 10:15:55 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_LSTITER:						 	   *
*	La función ft_lstiter recorre una lista enlazada y aplica  *
*	la función `f` a cada uno de sus nodos. La función `f`     *
*	debe tomar un puntero al contenido del nodo como argumento *
*	y no devuelve ningún valor.								   *
*															   *	
*	Argumentos:												   *
*	lst: Un puntero al primer nodo de la lista enlazada.       *
*	f: Una función que se aplicará a cada nodo de la lista.    *
*															   *
*	Devuelve: Nada (void).									   *
*															   *
\**************************************************************/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
void print_content(void *content)
{
    printf("Contenido: %s\n", (char *)content);
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

    ft_lstiter(lista, print_content);

    return (0);
}*/
