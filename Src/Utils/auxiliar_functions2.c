/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:05:59 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/15 17:26:46 by bautrodr         ###   ########.fr       */
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

int	skip_quotes(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && (str[i] != '\''))
		{
			if (str[i] == '\"')
				i += skip_quotes(str + i, 0);
			else
				i++;
		}
	}
	else
	{
		i++;
		while (str[i] && (str[i] != '\"'))
		{
			if (str[i] == '\'')
				i += skip_quotes(str + i, 0);
			else
				i++;
		}
	}
	return (i);
}

int	check_file(char **file, t_process *aux, t_redir *i)
{
	*file = get_ifile(aux->process, i->pos);
	if (*file && !access(*file, F_OK))
	{
		if (access(*file, R_OK))
			return (printf("%s: Permission denied\n", *file), free(*file), -1);
	}
	return (0);
}

void	ft_allocate(int comp, int *size, char ***aux, size_t len)
{
	if (comp != 0 && comp != (int)len)
		*aux = ft_calloc(*size + 1, sizeof(char *));
	else
		*aux = ft_calloc(--(*size) + 1, sizeof(char *));
}
