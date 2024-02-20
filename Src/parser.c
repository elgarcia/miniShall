/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:56:07 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/20 11:20:30 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	check_redaux(char **in, t_process **aux, int *i, t_redir **red_aux)
{
	if (ft_strnstr(*in, "<<", 3))
	{
		assign_redir(aux, i, red_aux, HD);
		if (ft_strlen(*in) > 2)
			ft_strlcpy(*in, *in + 2, ft_strlen(*in));
		else
			*i += 1;
	}
	else if (ft_strnstr(*in, "<", 2))
	{
		assign_redir(aux, i, red_aux, IRD);
		if (ft_strlen(*in) > 1)
			ft_strlcpy(*in, *in + 1, ft_strlen(*in));
		else
			*i += 1;
	}
	else if (ft_strnstr(*in, ">", 2))
	{
		assign_redir(aux, i, red_aux, ORD);
		if (ft_strlen(*in) > 1)
			ft_strlcpy(*in, *in + 1, ft_strlen(*in));
		else
			*i += 1;
	}
}

void	check_red(char **in, t_process **aux, int *i, t_redir **red_aux)
{
	if (ft_strnstr(*in, "|", 2))
	{
		(*aux)->next = (t_process *)ft_calloc(1, sizeof(t_process));
		(*aux)->next->n_process = (*aux)->n_process + 1;
		*aux = (*aux)->next;
		(*aux)->rd = NULL;
		*red_aux = (*aux)->rd;
		(*aux)->process = NULL;
		(*aux)->n_redis = *i + 1;
		(*aux)->next = NULL;
		if (ft_strlen(*in) > 2)
			ft_strlcpy(*in, *in + 1, ft_strlen(*in));
		else
			*i += 1;
	}
	else if (ft_strnstr(*in, ">>", 3))
	{
		assign_redir(aux, i, red_aux, APND);
		if (ft_strlen(*in) > 2)
			ft_strlcpy(*in, *in + 2, ft_strlen(*in));
		else
			*i += 1;
	}
	else
		check_redaux(in, aux, i, red_aux);
	if (!(*aux)->rd && (*red_aux) && (*aux)->process)
		(*aux)->rd = *red_aux;
}

void	new_proc(t_process **aux, t_shell *all, int n_proc, t_redir **red_aux)
{
	*aux = (t_process *)ft_calloc(1, sizeof(t_process));
	(*aux)->process = NULL;
	(*aux)->next = NULL;
	(*aux)->n_process = n_proc;
	(*aux)->n_redis = 0;
	(*aux)->rd = NULL;
	*red_aux = (*aux)->rd;
	if (all->lst_process == NULL)
		all->lst_process = *aux;
}

int	input_parser(char *line, t_shell *new)
{
	int			i;
	t_process	*aux;
	t_redir		*red_aux;
	
	aux = new->lst_process;
	i = 0;
	new->input = echo_split(line, ' '); // cambie el ft_split por mi echo_split
	if (!new->input)
		return (-1);
	while (new->input[i])
	{
		if (i == 0)
			new_proc(&aux, new, 0, &red_aux);
		check_red(&new->input[i], &aux, &i, &red_aux);
		if (new->input[i])
		{
			if (aux->process != NULL)
				aux->process = ft_strjoinup(&aux->process, " ");
			else
				new->n_process += 1;
			aux->process = ft_strjoinup(&aux->process, new->input[i]);
			i++;
		}
		else
			break;
	}
	return (ft_free(new->input, arg_counter(new->input)), 0); // cambie ft_word_count por arg_counter
}
