/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:05:59 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/10 13:35:39 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes2(char *str)
{
	int	i;

	i = 0;
	if (!str || !(*str))
		return (0);
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
    if (fd == -1)
        exit_error("open failed");
	line = get_next_line(fd);
	while (line)
	{
		write(all->og_outfile, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	skip_quotes(char *str, int i, int j)
{
	int	flag;
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	if (j == '\'')
		flag = -1;
	else
		flag = -2;
	while (str[i] && !(is_rd_ch(str[i]) && flag == 1))
	{
		if (str[i] == '\"')
			dquote++;
		if (str[i] == '\'')
			squote++;
		if ((dquote % 2 == 0 && flag == -2) || (squote % 2 == 0 && flag == -1))
			flag = 1;
		i++;
	}
	if (flag < 0)
		return (-1);
	return (i);
}

int	check_file(char **file, t_process *aux, t_redir *i)
{
	*file = get_ifile(aux->process, i->pos);
	if (*file && !access(*file, F_OK))
	{
		if (access(*file, R_OK))
			return (ft_fprintf(2, "%s: Permission denied\n", *file),
				free(*file), -1);
	}
	return (0);
}

void	ft_allocate(int comp, int *size, char ***aux, size_t len)
{
	if (comp != 0 && comp != (int)len)
		*aux = malloc_safe(*size + 1, sizeof(char *));
	else
		*aux = malloc_safe(--(*size) + 1, sizeof(char *));
}
