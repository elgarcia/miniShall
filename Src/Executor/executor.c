/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:02:48 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/13 12:01:06 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"
#include <sys/wait.h>

void	here_doc(t_shell *all, t_process *aux, int rd)
{
	char	*line;
	char	*outword;

	line = NULL;
	outword = NULL;
	if (rd != -1)
	{
		outword = get_ifile(aux->process, rd);
		outword = ft_strjoin(outword, "\n");
	}
	read_file(all, rd, line, outword);
	if (rd != -1)
		free(outword);
	if (all->fd_in == -1)
		exit(EXIT_SUCCESS);
}

static void	exec_type_aux(t_shell *all, t_process *aux, t_redir *i)
{
	char	*file;

	if (i->type == ORD || i->type == IRD)
	{
		file = get_ifile(aux->process, i->pos);
		if (i->type == ORD)
		{
			all->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (all->fd_out == -1)
				return (free(file), exit(EXIT_FAILURE));
			dup2(all->fd_out, STDOUT_FILENO);
		}
		else
		{
			all->fd_in = open(file, O_RDONLY);
			if (all->fd_in == -1)
				return (printf("%s: %s\n", file, strerror(errno)), \
				free(file), exit(EXIT_FAILURE));
			dup2(all->fd_in, STDIN_FILENO);
		}
		free(file);
	}
}

void	exec_type(t_shell *all, t_process *aux)
{
	t_redir	*i;
	char	*file;
	int		hd;

	hd = -1;
	i = aux->rd;
	while (i)
	{
		if (i->type == APND)
		{
			file = get_ifile(aux->process, i->pos);
			all->fd_out = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (all->fd_out == -1)
				return (free(file), exit(EXIT_FAILURE));
			dup2(all->fd_out, STDOUT_FILENO);
			free(file);
		}
		else if (i->type == HD)
			hd = i->pos;
		else
			exec_type_aux(all, aux, i);
		i = i->next;
	}
	if (aux->next)
		dup2(all->pipes[1], STDOUT_FILENO);
	if (hd != -1 || check_cats(all, aux) == 1)
		return (here_doc(all, aux, hd));
}

void	exec_son(t_shell *all, t_process *aux)
{
	char	**envp;

	if (check_builtins(all, aux))
	{
		if (aux->next)
			exit(EXIT_SUCCESS);
	}
	else if (!check_command(all, &aux, &all->exec_args))
	{
		envp = list_to_array(all->paths->env_lst);
		exec_type(all, aux);
		execve(all->exec_args[0], all->exec_args, envp);
	}
	else
		exit(g_exit_status);
}

void	exec_process(t_shell *all, int i, int j, int status)
{
	t_process	*aux;

	init_executor(all, &aux, &i, &j);
	while (aux)
	{
		init_pipex(all, aux, &all->sons[i]);
		if (all->sons[i] == 0)
		{
			set_signals(1);
			exec_son(all, aux);
		}
		else
			pipe_man(all);
		aux = aux->next;
		i++;
	}
	while (j < i)
	{
		waitpid(all->sons[j++], &status, 0);
		check_status(all, status);
	}
	reset_prc(all);
}
