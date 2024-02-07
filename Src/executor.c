/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:02:48 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/07 16:50:03 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	close_pipes(t_shell *all)
{
	dup2(all->og_infile, STDIN_FILENO);
	dup2(all->og_outfile, STDOUT_FILENO);
	all->fd_in = -1;
	all->fd_out = -1;
}

void	close_fds(t_shell *all)
{
	close(all->fd_out);
	close(all->fd_in);
}

void	exec_type(t_shell *all, t_process *aux)
{
	char	**split;
	char	*file;

	split = ft_split(aux->process, ' ');
	file = get_ifile(aux->process, arg_counter(split) - 1);
	if (aux->type == ORD)
	{
		all->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, 0666);
		if (all->fd_out == -1)
			exit(EXIT_FAILURE);
		dup2(all->fd_out, STDOUT_FILENO);
	}
	else if (aux->type == IRD)
	{
		all->fd_in = open(file, O_RDONLY);
		if (all->fd_in == -1)
		{
			printf("%s: %s\n", file, strerror(errno));
			exit(EXIT_FAILURE);
		}
		dup2(all->fd_in, STDIN_FILENO);
	}
	else if (aux->type == APND)
	{
		all->fd_out = open(file, O_WRONLY | O_APPEND | O_CREAT | O_NONBLOCK, 0666);
		if (all->fd_out == -1)
			exit(EXIT_FAILURE);
		dup2(all->fd_out, STDOUT_FILENO);
	}
	else
	{
		if (all->n_process > 1)
			dup2(all->pipes[1], STDOUT_FILENO);
	}
	ft_free(split, arg_counter(split));
	free(file);
}

void	exec_process(t_shell *all, char *line)
{
	t_process	*aux;
	int			i;
	int			j;

	i = 0;
	j = 0;
	all->exec_args = NULL;
	aux = all->lst_process;
	while (aux)
	{
		init_pipex(all, aux, &all->sons[i]);
		set_signals(1);
		if (all->sons[i] == 0)
		{
			exec_type(all, aux);
			if (check_builtins(all, line))
			{
				if (all->n_process > 1)
					exit(EXIT_SUCCESS);
			}
			else if (!check_command(all, &aux, &all->exec_args, aux->type))
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			else
				exit(EXIT_FAILURE);
		}
		else
		{
			close(all->pipes[1]);
			if (all->n_process > 1)
				dup2(all->pipes[0], STDIN_FILENO);
		}
		aux = aux->next;
		i++;
	}
	while (j != i)
		waitpid(all->sons[j++], NULL, 0);
	close_pipes(all);
	free_prcs(all);
}
