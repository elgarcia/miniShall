/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:56:07 by eliagarc          #+#    #+#             */
/*   Updated: 2024/04/08 12:53:14 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	check_redaux(char **in, t_process **aux, int *i, t_redir **red_aux)
{
	if (ft_strnstr(*in, "<<", 2))
	{
		assign_redir(aux, i, red_aux, HD);
		*i += 1;
	}
	else if (ft_strnstr(*in, "<", 1))
	{
		assign_redir(aux, i, red_aux, IRD);
		*i += 1;
	}
	else if (ft_strnstr(*in, ">", 1))
	{
		assign_redir(aux, i, red_aux, ORD);
		*i += 1;
	}
}

void	check_red(char **in, t_process **aux, int *i, t_redir **red_aux)
{
	if (!ft_strcmp(*in, "|"))
	{
		(*aux)->next = (t_process *)ft_calloc(1, sizeof(t_process));
		(*aux)->next->n_process = (*aux)->n_process + 1;
		*aux = (*aux)->next;
		(*aux)->rd = NULL;
		*red_aux = (*aux)->rd;
		(*aux)->process = NULL;
		(*aux)->n_redis = *i + 1;
		(*aux)->next = NULL;
		*i += 1;
	}
	else if (ft_strnstr(*in, ">>", 2))
	{
		assign_redir(aux, i, red_aux, APND);
		*i += 1;
	}
	else
		check_redaux(in, aux, i, red_aux);
	if (!(*aux)->rd && (*red_aux))
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

void	parse_arg(t_process **aux, t_shell *new, int *i, t_redir *red_aux)
{
	check_red(&new->input[*i], aux, i, &red_aux);
	if ((*aux)->process != NULL)
		(*aux)->process = ft_strjoinup(&(*aux)->process, " ");
	else
		new->n_process += 1;
	(*aux)->process = ft_strjoinup(&(*aux)->process, new->input[*i]);
	*i += 1;
}

int	input_parser(char *line, t_shell *new, int i)
{
	t_process	*aux;
	t_redir		*red_aux;

	aux = new->lst_process;
	new->input = echo_split(line, ' ');
	if (separate_rd(&new->input, -1) == -1)
		return (ft_free(&new->input, arg_counter(new->input)), -1);
	while (new->input[i])
	{
		if (i == 0)
			new_proc(&aux, new, 0, &red_aux);
		if (has_quotes2(new->input[i]) == 0)
			check_red(&new->input[i], &aux, &i, &red_aux);
		if (new->input[i])
			parse_arg(&aux, new, &i, red_aux);
	}
	if (there_is_rd(new->lst_process) || is_ao(new->input[i - 1]))
	{
		ft_fprintf(2, "Syntax error\n");
		free_prcs(new);
		g_exit_status = 258;
		return (ft_free(&new->input, arg_counter(new->input)), -1);
	}
	return (ft_free(&new->input, arg_counter(new->input)), 0);
}
