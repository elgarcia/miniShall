/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:30:16 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/07 14:11:46 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_rd(t_process *prc, int rd, int rd2)
{
	t_redir	*aux;

	aux = prc->rd;
	while (aux)
	{
		if (aux->type == rd || aux->type == rd2)
			return (1);
		aux = aux->next;
	}
	return (0);
}

int	is_rd_ch(char ch)
{
	if (ch == '>')
		return (1);
	else if (ch == '<')
		return (1);
	else if (ch == '|')
		return (1);
	return (0);
}

void	trim_outword(char *outword)
{
	int	i;
	int	j;
	int	aux;

	i = 0;
	j = 0;
	aux = 0;
	while (outword[i] != '\0')
	{
		if (outword[i] == '\'' || outword[i] == '\"')
		{
			aux = i;
			j = aux++;
			while (outword[aux])
				outword[j++] = outword[aux++];
			outword[j] = '\0';
		}
		else
			i++;
	}
}

void	read_loop(t_shell *all, int fd_aux, char **line, char **split)
{
	if (fd_aux == -1 && all->fd_out == -1 && arg_counter(split) > 1)
		write(all->fd_in, *line, ft_strlen(*line));
	free(*line);
	*line = get_next_line(all->og_infile);
}
