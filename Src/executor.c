/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:02:48 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/20 12:37:06 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"
#include <sys/wait.h>

void	here_doc(t_shell *all, t_process *aux, int rd)
{
	char	*line;
	char	*outword;

	outword = get_ifile(aux->process, rd);
	outword = ft_strjoin(outword, "\n");
	line = get_next_line(STDIN_FILENO);
	while(ft_strcmp(outword, line))
	{
		if (all->fd_out != -1)
			write(all->fd_out, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(outword);
}

static void	exec_type_aux(t_shell *all, t_process *aux, t_redir *i, int split)
{
	if (i->type == ORD || i->type == IRD)
	{
		if ((split - 1) == 0)
			return (printf("minishell: syntax error\n"), exit(EXIT_FAILURE));
		if (i->type == ORD)
		{
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
	else if (aux->next)
		dup2(all->pipes[1], STDOUT_FILENO);
}

void	exec_type(t_shell *all, t_process *aux, int split)
{
	t_redir	*i;
	int		hd;

	hd = 0;
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
			hd = i->pos;
		else
			exec_type_aux(all, aux, i, split);
		i = i->next;
	}
	if (aux->next)
		dup2(all->pipes[1], STDOUT_FILENO);
	if (hd != 0)
		return (here_doc(all, aux, hd), exit(EXIT_SUCCESS));
}

void	exec_process(t_shell *all)
{
	t_process	*aux;
	int			i;
	int			j;
	int			status;

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
			if (check_builtins(all, aux))
			{
				if (aux->next)
					exit(EXIT_SUCCESS);
			}
			else if (!check_command(all, &aux, &all->exec_args))
			{
				exec_type(all, aux, ft_word_count(aux->process, ' '));
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			}
			else
				exit(127);
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
	{
		waitpid(all->sons[j++], &status, 0);
		if (WIFEXITED(status) && !is_builting(all->lst_process)) // get exit status from not-builtins
			g_exit_status = WEXITSTATUS(status);
	}
	dup2(all->og_infile, STDIN_FILENO);
	dup2(all->og_outfile, STDOUT_FILENO);
	free_prcs(all);
}
