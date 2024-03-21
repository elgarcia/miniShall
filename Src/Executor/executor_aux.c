/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:44:15 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/21 18:03:45 by elias            ###   ########.fr       */
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

void	read_file(t_shell *all, int rd, char *line, char *outword)
{
	int	fd_aux;

	if (all->fd_in == -1 && rd > 0)
		fd_aux = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	line = get_next_line(all->og_infile);
	while (outword && ft_strcmp(outword, line))
	{
		if (all->fd_out != -1 && \
		!ft_strncmp(all->lst_process->process, "cat", 3))
			write(all->fd_out, line, ft_strlen(line));
		if (all->fd_in == -1 && rd > 0)
			write(fd_aux, line, ft_strlen(line));
		free(line);
		line = get_next_line(all->og_infile);
	}
	free(line);
	close(fd_aux);
	if (all->fd_in == -1  && rd > 0)
	{
		if (all->fd_in == -1 && \
		!ft_strncmp(all->lst_process->process, "cat", 3))
			write_file(all, fd_aux, line);
		close(fd_aux);
		unlink(".temp.txt");
	}
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
