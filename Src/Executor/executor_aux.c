/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:44:15 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/25 16:27:19 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_prc(t_shell *all)
{
	dup2(all->og_infile, STDIN_FILENO);
	dup2(all->og_outfile, STDOUT_FILENO);
	free_prcs(all);
}

void	pipe_man(t_shell *all)
{
	close(all->pipes[1]);
	if (all->n_process > 1)
		dup2(all->pipes[0], STDIN_FILENO);
}

void	init_executor(t_shell *all, t_process **aux, int *i, int *j)
{
	*i = 0;
	*j = 0;
	all->exec_args = NULL;
	*aux = all->lst_process;
}
