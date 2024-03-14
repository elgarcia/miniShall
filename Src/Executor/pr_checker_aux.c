/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_checker_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:24:46 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/09 21:35:05 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prcs(t_shell *all)
{
	t_process	*aux;

	aux = all->lst_process;
	while (aux)
	{
		aux = aux->next;
		free(all->lst_process->process);
		free(all->lst_process->rd);
		free(all->lst_process);
		all->lst_process = aux;
	}
	all->n_process = 0;
	all->lst_process = NULL;
}

char	*get_commad(t_process *prc, char **split)
{
	char	*ret;

	ret = NULL;
	if (prc->rd->pos == 0)
	{
		return (ft_substr(prc->process, ft_strlen(split[0]),
				ft_strlen(prc->process)));
	}
	else
	{
		if (arg_counter(split) > 2)
		{
			ret = ft_strjoin(split[0], " ");
			return (ft_strjoinup(&ret, split[1]));
		}
		else
			return (ft_strdup(split[0]));
	}
}

static void	execute_builtin2(t_shell *all, t_process *prc, char **aux)
{
	if (!ft_strncmp(aux[0], "history", 8))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '), -1);
		print_history(all);
	}
	else if (!ft_strncmp(aux[0], "exit", 5))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '), -1);
		ft_exit(all, prc->process);
	}
}

void	execute_builtin(t_shell *all, t_process *prc)
{
	char	**aux;

	aux = echo_split(prc->process, ' ');
	if (!ft_strncmp(aux[0], "export", 7))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '), -1);
		ft_export(all->paths, aux, 1);
	}
	else if (!ft_strncmp(aux[0], "unset", 6))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '), -1);
		ft_unset(all->paths, aux);
	}
	else if (!ft_strncmp(aux[0], "env", 4))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '), -1);
		ft_env(all->paths, aux);
	}
	else
		execute_builtin2(all, prc, aux);
}
