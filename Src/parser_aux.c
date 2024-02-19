/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:25:42 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/19 08:37:15 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	assign_redir(t_process **aux, int *i, t_redir **red_aux, int rd_type)
{
	if ((*red_aux))
	{
		(*red_aux)->next = (t_redir *)ft_calloc(1, sizeof(t_redir));
		(*red_aux) = (*red_aux)->next;
	}
	else
		(*red_aux) = (t_redir *)ft_calloc(1, sizeof(t_redir));
	(*red_aux)->type = rd_type;
	(*red_aux)->pos = *i - (*aux)->n_redis;
	(*red_aux)->next = NULL;
	(*aux)->n_redis += 1;
}
