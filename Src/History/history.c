/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:57:55 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 20:45:14 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open(shell->history_path, O_RDONLY);
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
	if (close(fd) == -1)
        exit_error("close failed 1");
}

int	calculate_current_index(int temp_fd)
{
	int		current_index;
	char	buffer[42];
	ssize_t	bytes_read;
	ssize_t	i;

	current_index = 1;
	while (1)
	{
		i = 0;
		bytes_read = read(temp_fd, buffer, sizeof(buffer));
		if (bytes_read <= 0)
			break ;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				current_index++;
			i++;
		}
	}
	return (current_index);
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

void	add_to_history(t_shell *shell, const char *line)
{
	int		history_fd;
	int		temp_fd;
	int		current_index;
	char	*formatted_line;

	history_fd = open_history_file(shell->history_path,
			O_WRONLY | O_APPEND | O_CREAT, 0666);
	temp_fd = open_history_file(shell->history_path, O_RDONLY, 0666);
	current_index = calculate_current_index(temp_fd);
	formatted_line = format_line(line, current_index);
	add_line_to_history(history_fd, formatted_line);
	free(formatted_line);
	close_file(temp_fd);
	close_file(history_fd);
}
