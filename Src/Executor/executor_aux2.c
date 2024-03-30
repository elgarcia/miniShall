/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:30:16 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/30 11:01:43 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_rd(t_process *prc, int rd)
{
	t_redir	*aux;

	aux = prc->rd;
	while (aux)
	{
		if (aux->type == rd)
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
