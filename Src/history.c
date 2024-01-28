/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:57:55 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/26 09:52:35 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	print_history(void)
{
	int	fd;
	char	*line;
	
	fd = open("/Users/tuta/tuta/coding/miniShall/history", O_RDONLY);
	if (fd == -1)
		ft_fprintf(2, "Error: Could not read history file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	open_history_file(const char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	close_file(int fd)
{
	if (close(fd) == -1)
	{
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
}

int	calculate_current_index(int temp_fd)
{
	int		current_index;
	char	buffer[1024];
	ssize_t	bytes_read;
	ssize_t	i;

	i = 0;
	current_index = 1;
	while ((bytes_read = read(temp_fd, buffer, sizeof(buffer))) > 0)
	{
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				current_index++;
			i++;
		}
	}
	return (current_index);
}

void	error_exit(void)
{
	perror("Memory allocation error");
	exit(EXIT_FAILURE);
}

char	*format_line(const char *line, int current_index)
{
	char	*index_str;
	char	*formatted_line;
	char	*temp;

	index_str = ft_itoa(current_index);
	formatted_line = ft_strjoin(index_str, ": ");
	free(index_str);
	if (formatted_line == NULL)
		error_exit();
	temp = ft_strjoin(formatted_line, line);
	free(formatted_line);
	if (temp == NULL)
		error_exit();
	formatted_line = ft_strjoin(temp, "\n");
	free(temp);
	if (formatted_line == NULL)
		error_exit();
	return (formatted_line);
}

void	add_line_to_history(int history_fd, char *formatted_line)
{
	if (ft_fprintf(history_fd, "%s", formatted_line) < 0)
	{
		perror("Error writing to history file");
		free(formatted_line);
		close_file(history_fd);
		exit(EXIT_FAILURE);
	}
}

void	add_to_history(const char *line)
{
	int		history_fd;
	int		temp_fd;
	int		current_index;
	char	*formatted_line;

	history_fd = open_history_file("/Users/tuta/tuta/coding/miniShall/history", O_WRONLY | O_APPEND | O_CREAT, 0666);
	temp_fd = open_history_file("/Users/tuta/tuta/coding/miniShall/history", O_RDONLY, 0666);
	current_index = calculate_current_index(temp_fd);
	formatted_line = format_line(line, current_index);
	add_line_to_history(history_fd, formatted_line);
	free(formatted_line);
	close_file(temp_fd);
	close_file(history_fd);
}
