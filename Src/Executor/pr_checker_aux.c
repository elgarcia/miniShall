/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_checker_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:24:46 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/06 15:31:59 by eliagarc         ###   ########.fr       */
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
	char	*ret;

	ret = NULL;
	if (prc->rd->pos == 0)
	{
		return (ft_substr(prc->process, ft_strlen(split[0]),
				ft_strlen(prc->process)));
	}
	else
	{
		if (arg_counter(split) > 2 && split[1][0] == '-')
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
		exec_type(all, prc, -1);
		print_history(all);
	}
	else if (!ft_strncmp(aux[0], "exit", 5))
	{
		exec_type(all, prc, -1);
		ft_exit(all, prc->process);
	}
}

void	execute_builtin(t_shell *all, t_process *prc)
{
	char	**aux;

	aux = echo_split(prc->process, ' ');
	if (!aux)
		return ;
	if (!ft_strncmp(aux[0], "export", 7))
	{
		exec_type(all, prc, -1);
		ft_export(all->paths, aux, 1);
	}
	else if (!ft_strncmp(aux[0], "unset", 6))
	{
		exec_type(all, prc, -1);
		ft_unset(all->paths, aux);
	}
	else if (!ft_strncmp(aux[0], "env", 4))
	{
		exec_type(all, prc, -1);
		ft_env(all->paths);
	}
	else
		execute_builtin2(all, prc, aux);
	if (aux)
		ft_free(&aux, arg_counter(aux));
}
