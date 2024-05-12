/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:09:52 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/12 19:25:45 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	appnd_rd(t_shell *all, char **file)
{
	all->fd_out = open(*file, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (all->fd_out == -1)
		return (free(*file), all->exit_status = 1);
	if (dup2(all->fd_out, STDOUT_FILENO) == -1)
		exit_error("dup2 failed");
	free(*file);
	return (0);
}

int	in_rd(t_shell *all, char **file)
{
	if (all->fd_in == -1)
		return (ft_fprintf(2, "%s: %s\n", *file, strerror(errno)), \
		free(*file), all->exit_status = 1);
	if (dup2(all->fd_in, STDIN_FILENO) == -1)
		exit_error("dup2 failed");
	close(all->fd_in);
	return (0);
}

void	rd_file(t_shell *all, int fd_aux, char **split, int *mypipe)
{
	if (fd_aux == -1 && arg_counter(split) > 1)
	{
		all->fd_in = mypipe[0];
		if (dup2(all->fd_in, STDIN_FILENO) == -1)
			exit_error("dup2 failed");
		if (close(all->fd_in) == -1)
			exit_error("close failed 7");
		all->fd_in = -1;
	}
}
