/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:00:52 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 10:12:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************
*						FT_LSTDELONE:					   	   *
*	La función ft_lstdelone elimina y libera la memoria de     *
*	un solo nodo de una lista enlazada representada por un     *
*	puntero `lst`. Además, toma como argumento una función     *
*	`del` que se utiliza para liberar la memoria del contenido *
*	del nodo que se eliminará.								   *
*															   *
*	Argumentos:												   *
*	lst: Un puntero al nodo que se eliminará y liberará.	   *
*	del: Una función que toma un puntero al contenido del      *
*	     nodo y libera la memoria asociada a ese contenido.	   *
*															   *
*	Devuelve: Nada (void).									   *
*															   *
\**************************************************************/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	else
	{
		del(lst->content);
		free(lst);
	}
}
/*
#include <stdio.h>
void del(void *content)
{
    free(content);
}

int	main(void)
{
    char *contenido = strdup("Contenido del nodo");
    t_list *nodo = ft_lstnew(contenido);

    if (nodo) {
        printf("Contenido antes de eliminar: %s\n", (char *)nodo->content);
        ft_lstdelone(nodo, del);
    }
	printf("Contenido despues de eliminar: <%s>\n", (char *)nodo->content);
    return (0);
}*/
