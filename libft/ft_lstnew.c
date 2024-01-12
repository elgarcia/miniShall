/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:02:42 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 09:46:59 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_LSTNEW:						       *
*	La función ft_lstnew crea un nuevo nodo de lista enlazada  *
*	(t_list) con el contenido especificado y lo inicializa     *
*	adecuadamente. El nuevo nodo se asigna dinámicamente y     *
*	se establecen los punteros `content` y `next` según los    *
*	valores proporcionados.									   *
*															   *	
*	Argumentos:												   *
*	content: Un puntero al contenido que se almacenará en el   *
*	         nodo de la lista.								   *
*															   *
*	Devuelve: Un puntero al nuevo nodo de lista enlazada, o    *
*	NULL si hay un error de asignación de memoria.			   *
*															   *
\**************************************************************/

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
#include <stdio.h>
int	main(void)
{
    t_list *nuevo_nodo = ft_lstnew("Este es el contenido del nodo");

    if (nuevo_nodo)
	{
        printf("Contenido del nuevo nodo: %s\n", (char *)nuevo_nodo->content);
        printf("Puntero al siguiente nodo: %p\n", (void *)nuevo_nodo->next);
    } 
	else
		printf("Error al crear el nuevo nodo.\n");

    free(nuevo_nodo);

    return (0);
}*/
