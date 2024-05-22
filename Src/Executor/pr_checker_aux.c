/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_checker_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:24:46 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/22 15:03:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prcs(t_shell *all)
{
	t_process	*aux;
	t_process	*tmp;
	t_redir		*r_aux;
	t_redir		*tmp_r;

	aux = all->lst_process;
	tmp = all->lst_process;
	r_aux = all->lst_process->rd;
	tmp_r = all->lst_process->rd;
	while (aux)
	{
		tmp = tmp->next;
		while (r_aux)
		{
			tmp_r = tmp_r->next;
			free(r_aux);
			r_aux = tmp_r;
		}
		free(aux->process);
		free(aux);
		aux = tmp;
	}
	all->n_process = 0;
	all->lst_process = NULL;
}

char	*get_commad(t_process *prc, char **split)
{
	if (prc->rd && prc->rd->pos == 0)
	{
		return (ft_substr(prc->process, ft_strlen(split[0]),
				ft_strlen(prc->process)));
	}
	else
		return (ft_strdup(prc->process));
}

void	execute_builtin(t_shell *all, t_process *prc)
{
	char	**aux;

	aux = split_words(prc->process);
	if (!ft_strncmp(aux[0], "export", 7))
		all->exit_status = ft_export(all->paths, aux);
	else if (!ft_strncmp(aux[0], "unset", 6))
		ft_unset(all->paths, aux);
	else if (!ft_strncmp(aux[0], "env", 4))
		ft_env(all->paths);
	else if (!ft_strncmp(aux[0], "history", 8))
		print_history(all);
	else if (!ft_strncmp(aux[0], "exit", 5))
	{
		ft_free(&aux, arg_counter(aux));
		ft_exit(all, prc->process);
		return ;
	}
	ft_free(&aux, arg_counter(aux));
}
