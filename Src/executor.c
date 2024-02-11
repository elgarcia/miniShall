/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:02:48 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/11 17:59:33 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	here_doc(t_process *aux, int rd)
{
	char	*line;
	char	*outword;

	outword = get_ifile(aux->process, rd);
	outword = ft_strjoin(outword, "\n");
	line = get_next_line(STDIN_FILENO);
	while(ft_strcmp(outword, line))
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(outword);
	if (aux->rd->pos == 1)
		exit(EXIT_SUCCESS);
}

static void	exec_type_aux(t_shell *all, t_process *aux, t_redir *i, int split)
{
	if (i->type == ORD || i->type == IRD)
	{
		if ((split - 1) == 0)
			return (printf("minishell: syntax error\n"), exit(EXIT_FAILURE));
		if (i->type == ORD)
		{
			printf("%d\n", i->pos);
			all->fd_out = open(get_ifile(aux->process, i->pos), O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, 0666);
			if (all->fd_out == -1)
				exit(EXIT_FAILURE);
			dup2(all->fd_out, STDOUT_FILENO);
		}
		else
		{
			all->fd_in = open(get_ifile(aux->process, i->pos), O_RDONLY);
			if (all->fd_in == -1)
				return (printf("%s: %s\n", get_ifile(aux->process, i->pos), strerror(errno)), exit(EXIT_FAILURE));
			dup2(all->fd_in, STDIN_FILENO);	
		}
	}
	else
	{
		if (all->n_process > 1)
			dup2(all->pipes[1], STDOUT_FILENO);
	}
}

void	exec_type(t_shell *all, t_process *aux, int split)
{
	t_redir	*i;

	i = aux->rd;
	while (i)
	{
		if (i->type == APND)
		{
			all->fd_out = open(get_ifile(aux->process, i->pos), O_WRONLY | O_APPEND | O_CREAT | O_NONBLOCK, 0666);
			if (all->fd_out == -1)
				exit(EXIT_FAILURE);
			dup2(all->fd_out, STDOUT_FILENO);
		}
		else if (i->type == HD)
			here_doc(aux, i->pos);
		else
			exec_type_aux(all, aux, i, split);
		i = i->next;
	}
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
			if (check_builtins(all, line))
			{
				exec_type(all, aux, ft_word_count(aux->process, ' '));
				if (all->n_process > 1)
					exit(EXIT_SUCCESS);
			}
			else if (!check_command(all, &aux, &all->exec_args))
			{
				exec_type(all, aux, ft_word_count(aux->process, ' '));
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			}
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
