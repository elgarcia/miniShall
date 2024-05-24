/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:25:42 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/24 11:10:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_redir(t_process **aux, int *i, t_redir **red_aux, int rd_type)
{
	if ((*red_aux))
	{
		(*red_aux)->next = (t_redir *)malloc_safe(1, sizeof(t_redir));
		(*red_aux) = (*red_aux)->next;
	}
	else
		(*red_aux) = (t_redir *)malloc_safe(1, sizeof(t_redir));
	(*red_aux)->type = rd_type;
	(*red_aux)->pos = *i - (*aux)->n_redis;
	(*red_aux)->next = NULL;
	(*aux)->n_redis += 1;
}

int	is_ao(char *str)
{
	if (!ft_strncmp(str, "||", 3))
		return (1);
	else if (ft_strnstr(str, "&&", 3))
		return (1);
	else if (ft_strnstr(str, ";", 2))
		return (1);
	return (0);
}

int	check_cats(t_shell *all, t_process *aux, int flag)
{
	t_process	*p_aux;
	char		*tmp;

	p_aux = all->lst_process;
	while (p_aux)
	{
		tmp = ft_strdup(p_aux->process);
		remove_quotes_from_string(tmp);
		if (!ft_strncmp(tmp, "cat", 3))
			flag++;
		free(tmp);
		p_aux = p_aux->next;
	}
	tmp = ft_strdup(aux->process);
	remove_quotes_from_string(tmp);
	if (flag == all->n_process || ft_strcmp(tmp, "cat"))
		return (free(tmp), 0);
	if (!ft_strcmp(tmp, "cat"))
	{
		if (aux->n_process == all->n_process - 1)
			return (free(tmp), 0);
		return (free(tmp), 1);
	}
	return (free(tmp), 0);
}

void	check_exp(char **in, int *i, int j)
{
	if ((int)ft_strlen(*in) > j)
		ft_strlcpy(*in, *in + j, ft_strlen(*in));
	else
		*i += 1;
}

int	there_is_rd(t_process *lst)
{
	t_process	*aux;
	char		**split_aux;

	aux = lst;
	split_aux = NULL;
	while (aux)
	{
		if (!aux->process)
			return (ft_free(&split_aux, arg_counter(split_aux)), 1);
		split_aux = split_words(aux->process);
		if (is_rdp(split_aux))
			return (ft_free(&split_aux, arg_counter(split_aux)), 1);
		if (aux->rd)
		{
			if (aux->rd->pos == arg_counter(split_aux))
				return (ft_free(&split_aux, arg_counter(split_aux)), 1);
		}
		ft_free(&split_aux, arg_counter(split_aux));
		aux = aux->next;
	}
	return (ft_free(&split_aux, arg_counter(split_aux)), 0);
}
