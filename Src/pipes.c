/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:57:59 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/06 19:59:31 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	init_pipex(t_shell *all, t_process *prc, pid_t *pid)
{
	if (prc->n_process == 0 && !is_builting(prc))
		open_file(prc->process, &all->fd_in);
	if (prc->next || (!ft_strncmp(prc->process, "cat", 4)
			&& ft_strlen(prc->process) != 4))
	{
		if (pipe(all->pipes) == -1)
		{
			perror("Pipe failed!");
			exit(EXIT_FAILURE);
		}
	}
	if (prc->next || !is_builting(prc))
	{
		*pid = fork();
		if (*pid < 0)
		{
			perror("Fork failed!");
			exit(EXIT_FAILURE);
		}
	}
}

int	open_file(char *file, int *fd)
{
	char	*aux;

	aux = get_ifile(file, 1);
	if (!aux)
		return (0);
	if (access(aux, F_OK | R_OK) == -1)
		return (free(aux), -1);
	*fd = open(aux, O_RDONLY);
	if (*fd == -1)
	{
		perror("Failed to open output file");
		free(aux);
		return (-1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
		return (-1);
	free(aux);
	close(*fd);
	return (0);
}
