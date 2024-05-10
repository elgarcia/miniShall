/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:42:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 13:17:48 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_quote(int i, char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	check_pair_quotes(char *s, int *i, char c)
{
	int	n;

	n = 1;
	while (s[*i + 1] && s[*i + 1] != c)
		(*i)++;
	if (s[*i + 1] == c)
		n++;
	(*i)++;
	return (n);
}

int	check_opened_quotes(char *s, int simple, int doble)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
			doble += check_pair_quotes(s, &i, s[i]);
		if (s[i] == 39)
			simple += check_pair_quotes(s, &i, s[i]);
		if (doble % 2 != 0 || simple % 2 != 0)
		{
			ft_fprintf(2,"Quotes opened\n");
			return (0);
		}
	}
	return (1);
}
