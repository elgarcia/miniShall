/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:44:15 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/01 22:16:07 by eliagarc         ###   ########.fr       */
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

void	read_file(t_shell *all, int fd, char *line, char *outword)
{
	line = get_next_line(fd);
	while (outword && ft_strcmp(outword, line))
	{
		if (all->fd_out != -1)
			write(all->fd_out, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	count_rds(t_process *prcs)
{
	int		i;
	t_redir	*aux;

	i = 0;
	aux = prcs->rd;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}
