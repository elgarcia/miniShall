/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:56:07 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/11 17:48:56 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	check_redaux(char *in, t_process **aux, int *i, t_redir **red_aux)
{
	if (!ft_strncmp(in, "<<", 3))
	{
		(*red_aux) = (t_redir *)ft_calloc(1, sizeof(t_redir));
		(*red_aux)->type = HD;
		(*red_aux)->pos = *i - (*aux)->n_redis;
		(*red_aux)->next = NULL;
		*i += 1;
	}
	if (!ft_strncmp(in, "<", 2))
	{
		(*red_aux) = (t_redir *)ft_calloc(1, sizeof(t_redir));
		(*red_aux)->type = IRD;
		(*red_aux)->pos = *i - (*aux)->n_redis;
		(*red_aux)->next = NULL;
		*i += 1;
	}
	else if (!ft_strncmp(in, ">", 2))
	{
		(*red_aux) = (t_redir *)ft_calloc(1, sizeof(t_redir));
		(*red_aux)->type = ORD;
		(*red_aux)->pos = *i - (*aux)->n_redis;
		(*red_aux)->next = NULL;
		*i += 1;
	}
}

void	check_red(char *in, t_process **aux, int *i, t_redir **red_aux)
{
	if ((*red_aux))
		(*red_aux) = (*red_aux)->next;
	if (!ft_strncmp(in, "|", 2))
	{
		(*aux)->rd = (t_redir *)ft_calloc(1, sizeof(t_redir));
		(*aux)->rd->type = PIPE;
		(*aux)->next = (t_process *)ft_calloc(1, sizeof(t_process));
		(*aux)->next->n_process = (*aux)->n_process + 1;
		*aux = (*aux)->next;
		(*aux)->process = NULL;
		(*aux)->next = NULL;
		(*aux)->n_redis = *i + 1;
		(*aux)->rd = NULL;
		*i += 1;
	}
	else if (!ft_strncmp(in, ">>", 3))
	{
		(*red_aux) = (t_redir *)ft_calloc(1, sizeof(t_redir));
		(*red_aux)->type = APND;
		(*red_aux)->pos = *i - (*aux)->n_redis;
		(*red_aux)->next = NULL;
		*i += 1;
	}
	else
		check_redaux(in, aux, i, red_aux);
}

int		count_quotes(char **argv, int j)
{
	int	i;
	int	counter_d;
	int	counter_s;

	counter_d = 0;
	counter_s = 0;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'')
				counter_s++;
			if (argv[i][j] == '\"')
				counter_d++;
			j++;
		}
		i++;
	}
	if (counter_d % 2 == 0 || counter_s % 2 == 0)
		return (0);
	return (1);
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
	char		**split;

	split = echo_split(line, ' ');
	if (count_quotes(split, 0))
		return (ft_free(split, arg_counter(split)), -1);
	ft_free(split, arg_counter(split));
	aux = new->lst_process;
	i = 0;
	new->input = ft_split(line, ' ');
	if (!new->input)
		return (-1);
	while (new->input[i])
	{
		if (i == 0)
			new_proc(&aux, new, 0, &red_aux);
		check_red(new->input[i], &aux, &i, &red_aux);
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
	return (ft_free(new->input, ft_word_count(line, ' ')), 0);
}
