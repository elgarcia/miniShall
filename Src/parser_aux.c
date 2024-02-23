/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:25:42 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/23 18:53:29 by eliagarc         ###   ########.fr       */
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

int		is_ao(char *str)
{
	if (ft_strnstr(str, "||", 3))
		return (1);
	else if (ft_strnstr(str, "&&", 3))
		return (1);
	else if (ft_strnstr(str, ";", 2))
		return (1);
	return (0);
}

int		check_cats(t_shell *all, t_process *aux)
{
	t_process	*p_aux;
	int			flag;

	flag = 0;
	p_aux = all->lst_process;
	while (p_aux)
	{
		if (!ft_strncmp(p_aux->process, "cat", 3))
			flag++;
		p_aux = p_aux->next;
	}
	if (flag == all->n_process)
		return (0);
	if (!ft_strncmp(aux->process, "cat", 3))
	{
		if (aux->n_process == all->n_process - 1)
			return (0);
		return  (1);
	}
	return (0);
}
