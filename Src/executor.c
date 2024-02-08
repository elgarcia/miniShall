/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:02:48 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/08 20:51:14 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"
/*revisar*/
void	here_doc(t_process *aux)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while(line)
	{
		if (line == get_ifile(aux->process, 1))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

static void	exec_type_aux(t_shell *all, t_process *aux, char *file, int split)
{
	if (aux->type == ORD || aux->type == IRD)
	{
		if ((split - 1) == 0)
			return (printf("minishell: syntax error\n"), exit(EXIT_FAILURE));
		if (aux->type == ORD)
		{
			all->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, 0666);
			if (all->fd_out == -1)
				exit(EXIT_FAILURE);
			dup2(all->fd_out, STDOUT_FILENO);
		}
		else
		{
			all->fd_in = open(file, O_RDONLY);
			if (all->fd_in == -1)
				return (printf("%s: %s\n", file, strerror(errno)), exit(EXIT_FAILURE));
			dup2(all->fd_in, STDIN_FILENO);	
		}
	}
	if (aux->type == HD)
	{
		here_doc(aux);
	}
	free(file);
}

void	exec_type(t_shell *all, t_process *aux)
{
	int		split;
	char	*file;

	split = ft_word_count(aux->process, ' ');
	file = get_ifile(aux->process, split - 1);
	if (!file)
		exit(EXIT_FAILURE);
	if (aux->type == APND)
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
	exec_type_aux(all, aux, file, split);
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
