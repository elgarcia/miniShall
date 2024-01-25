/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:57:55 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/25 18:36:31 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	find_last_command_num(int fd)
{
	int		last_num;
	ssize_t	len;
	char	*aux;
	size_t	aux_len;
	char	*line;
	char tmp[11]; 

	last_num = 0;
	len = read(fd, tmp, 10);
	if (len > 0)
	{
		tmp[len] = '\0';
		aux = ft_strchr(tmp, ':');
		if (aux)
		{
			aux_len = ft_strlen(aux) - 1;
			line = ft_substr(aux, 0, aux_len);
			last_num = ft_atoi(line);
			free(line);
		}
	}
	return (last_num);
}

void	add_to_history(const char *history_file)
{
	int		fd;
	int		num;
	char	command[256];

	command[0] = '\0';
	fd = open(history_file, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error al abrir o crear el archivo de historial");
		exit(EXIT_FAILURE);
	}
	num = find_last_command_num(fd) + 1;
	g_exit_status = 0;
	close(fd);
}
