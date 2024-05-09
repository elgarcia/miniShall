/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:42:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 12:55:22 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_quote(int i, char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	count_words(char *s)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (s[++i])
	{
		if ((s[i] != 32 && s[i] != 34 && s[i] != 39)
			&& (s[i + 1] == 32 || s[i + 1] == '\0'
				|| s[i + 1] == 34 || s[i + 1] == 39))
			res++;
		if (s[i] == 34 || s[i] == 39)
		{
			res++;
			i = find_next_quote(i + 1, s, s[i]);
		}
	}
	return (res);
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
