/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:24:28 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 12:49:44 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_counter(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'')
			single_quotes++;
		else if (str[i] == '\"')
			double_quotes++;
		i++;
	}
	return (single_quotes % 2 != 0 || double_quotes % 2 != 0);
}

int	remove_char(char *str, char c)
{
	int	new;
	int	i;

	new = 0;
	i = 0;
	if (!quotes_counter(str))
	{
		while (str[i])
		{
			if (str[i] && str[i] != c)
				str[new ++] = str[i];
			i++;
		}
		str[new] = 0;
	}
	else
		return (1);
	return (0);
}
