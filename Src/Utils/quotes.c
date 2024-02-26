/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:32:46 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 17:56:50 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	check_quote_closure(char *str)
{
	int	i;
	int	type;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			type = str[i];
			i++;
			while (str[i] != '\0' && str[i] != type)
				i++;
		}
		if (str[i] == '\0')
			return (1);
		++i;
	}
	return (0);
}

static void	process_quoted_section(int *i, int *j, char *str, char quote)
{
	if (check_quote_closure(str + *i))
	{
		while (str[*i] != '\0')
		{
			str[*j] = str[*i];
			++(*j);
			++(*i);
		}
	}
	else
	{
		++(*i);
		while (str[*i] != quote)
		{
			str[*j] = str[*i];
			++(*j);
			++(*i);
		}
		++(*i);
	}
}

void	remove_quotes_from_string(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			process_quoted_section(&i, &j, str, '\'');
		else if (str[i] == '\"')
			process_quoted_section(&i, &j, str, '\"');
		else
		{
			str[j] = str[i];
			++j;
			++i;
		}
	}
	str[j] = '\0';
}

void	remove_quotes_from_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		remove_quotes_from_string(matrix[i]);
		++i;
	}
}