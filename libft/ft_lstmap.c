/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:31:18 by bautrodr          #+#    #+#             */
/*   Updated: 2023/09/21 10:35:46 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************	
*						FT_LSTMAP:							  *
*															  *
*    Itera la lista ’lst’ y aplica la función ’f’ al		  *
*	contenido de cada nodo. Crea una lista resultante		  *
*	de la aplicación correcta y sucesiva de la función		  *
*	’f’ sobre cada nodo. La función ’del’ se utiliza		  *
*	para eliminar el contenido de un nodo, si hace			  *
*	falta.													  *
*															  *	
*	Argumentos:												  *
*	lst: Un puntero al primer nodo de la lista enlazada.      *
*	f: Una función que se aplicará a cada nodo de la lista y  *
*	   debe devolver un puntero al nuevo contenido.			  *
*	del: Una función que se utilizará para liberar la memoria *
*	   del contenido original si es necesario.				  *
*															  *
*	Devuelve: Un puntero a la nueva lista enlazada con los    *
*	resultados de la aplicación de `f`, o NULL si falla la    *
*	creación de un nuevo nodo.								  *
*															  *
\*************************************************************/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	void	*cont;

	if (!f || !del || !lst)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		cont = f(lst->content);
		node = ft_lstnew(cont);
		if (!node)
		{
			del(cont);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>
void del(void *content)
{
    free(content);
}

void *convertir_a_mayusculas(void *content)
{
    char *cadena = (char *)content;
    size_t len = ft_strlen(cadena);
    for (size_t i = 0; i < len; i++)
	{
        cadena[i] = ft_toupper(cadena[i]);
    }
    return (void *)cadena;
}

int main()
{
    t_list *lista = NULL;
    t_list *elemento1 = ft_lstnew(strdup("Elemento 1"));
    t_list *elemento2 = ft_lstnew(strdup("Elemento 2"));
    t_list *elemento3 = ft_lstnew(strdup("Elemento 3"));
    
    ft_lstadd_back(&lista, elemento1);
    ft_lstadd_back(&lista, elemento2);
    ft_lstadd_back(&lista, elemento3);
	printf("Contenido antes de aplicar lstmap:\n%s\n%s\n%s\n",
				elemento1->content, elemento2->content, elemento3->content);
    t_list *nueva_lista = ft_lstmap(lista, convertir_a_mayusculas, del);

    t_list *nodo = nueva_lista;
    while (nodo) {
        printf("Contenido de la nueva lista: %s\n", (char *)nodo->content);
        nodo = nodo->next;
    }
    ft_lstclear(&nueva_lista, del);
    return (0);
}*/
