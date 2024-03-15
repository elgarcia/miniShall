/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:30:16 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/15 23:50:42 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_rd(t_process *prc, int rd)
{
	t_redir	*aux;

	aux = prc->rd;
	while (aux)
	{
		if (aux->type == rd)
			return (1);
		aux = aux->next;
	}
	return (0);
}
