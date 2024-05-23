/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:02:48 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/23 17:56:02 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	here_doc(t_shell *all, t_process *aux, int rd)
{
	char	*line;
	char	*outword;

	line = NULL;
	outword = NULL;
	set_signals(2);
	if (rd != -1)
	{
		outword = get_ifile(aux->process, rd);
		outword = ft_strjoin(outword, "\n");
		trim_outword(outword);
	}
	read_file(all, aux, line, outword);
	if (rd == -1)
		exit(all->exit_status);
	set_signals(1);
	if (rd != -1)
		free(outword);
}

static int	exec_type_aux(t_shell *all, t_process *aux, t_redir *i)
{
	char	*file;

	if (i->type == ORD || i->type == IRD)
	{
		if (check_file(&file, aux, i) == -1)
			return (all->exit_status = 1);
		if (i->type == ORD)
		{
			all->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (dup2(all->fd_out, STDOUT_FILENO) == -1)
				exit_error("dup2 failed");
		}
		else
		{
			all->fd_in = open(file, O_RDONLY);
			if (in_rd(all, &file) == 1)
				return (all->exit_status);
		}
		free(file);
	}
	else if (i->type == HD)
		here_doc(all, aux, i->pos);
	return (0);
}

int	exec_type(t_shell *all, t_process *aux, int hd)
{
	t_redir	*i;
	char	*file;

	i = aux->rd;
	while (i)
	{
		if (i->type == APND)
		{
			file = get_ifile(aux->process, i->pos);
			if (appnd_rd(all, &file) == 1)
				return (all->exit_status);
		}
		else
			if (exec_type_aux(all, aux, i) == 1)
				return (all->exit_status);
		i = i->next;
	}
	if (aux->next && !search_rd(aux, ORD, APND))
	{
		if (dup2(all->pipes[1], STDOUT_FILENO) == -1)
			exit_error("dup2 failed");
	}
	if (check_cats(all, aux) == 1)
		return (here_doc(all, aux, hd), 0);
	return (0);
}

void	exec_son(t_shell *all, t_process *aux)
{
	char	**envp;
	int		flag;

	flag = 0;
	if (exec_type(all, aux, -1) == 1)
		exit(all->exit_status);
	if (check_builtins(all, aux))
	{
		if (all->n_process > 1)
			exit(all->exit_status);
	}
	else
	{
		flag = check_command(all, &aux, &all->exec_args);
		if (flag != -2 && flag != -1)
		{
			envp = list_to_array(all->paths->env_lst);
			execve(all->exec_args[0], all->exec_args, envp);
		}
		exit(all->exit_status);
	}
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
		else if (aux->next)
			pipe_man(all);
		aux = aux->next;
		i++;
	}
	while (j < i)
	{
		if (waitpid(all->sons[j++], &status, 0) == all->sons[i - 1])
			check_status(all, status);
	}
	reset_prc(all);
}
