/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:30:16 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/22 18:48:58 by eliagarc         ###   ########.fr       */
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

int	is_rd_ch(char ch)
{
	if (ch == '>')
		return (1);
	else if (ch == '<')
		return (1);
	else if (ch == '|')
		return (1);
	return (0);
}
