/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:05:59 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/13 12:32:33 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	write_file(t_shell *all, int fd, char *line)
{
	fd = open(".temp.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		write(all->og_outfile, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	skip_quotes(char *str)
{
	int	i;

	i = 1;
	while (str[i] && (str[i] != '\'' && str[i] != '\"'))
		i++;
	if (str[i])
		i++;
	return (i);
}
