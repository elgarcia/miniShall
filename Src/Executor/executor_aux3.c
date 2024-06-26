/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:09:52 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/22 11:10:40 by bautrodr         ###   ########.fr       */
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
		return (ft_fprintf(2, "%s: %s\n", *file, strerror(errno)), free(*file),
			all->exit_status = 1);
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

int	check_quoted_string(char **command)
{
	size_t	i;
	int		opt;

	opt = -1;
	i = 0;
	if (*command[0] == '\'')
		opt = 1;
	if (*command[0] == '\"')
		opt = 2;
	if (opt == -1)
		return (1);
	while (i < ft_strlen(*command))
	{
		if (opt == 1 && (*command)[i] != '\'')
			return (0);
		if (opt == 2 && (*command)[i] != '\"')
			return (0);
		i++;
	}
	free(*command);
	*command = ft_strdup(" ");
	return (1);
}
