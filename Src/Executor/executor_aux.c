/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:44:15 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/07 14:10:48 by eliagarc         ###   ########.fr       */
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

void	read_file(t_shell *all, t_process *prc, char *line, char *outword)
{
	int		fd_aux;
	char	**split;

	fd_aux = 0;
	split = ft_split(prc->process, ' ');
	if (all->fd_in == -1 && arg_counter(split) > 1)
	{
		fd_aux = -1;
		all->fd_in = open(".temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	line = get_next_line(all->og_infile);
	while (outword && ft_strcmp(outword, line))
		read_loop(all, fd_aux, &line, split);
	close(all->fd_in);
	if (fd_aux == -1 && arg_counter(split) > 1)
	{
		all->fd_in = open(".temp.txt", O_RDONLY);
		dup2(all->fd_in, STDIN_FILENO);
		close(all->fd_in);
		all->fd_in = -1;
	}
	return (free(line), ft_free(&split, arg_counter(split)));
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
