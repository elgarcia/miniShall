/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/13 15:31:39 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_split_words(char *s, char **arg)
{
	int	pos;
	int	start;
	int	i;

	start = 0;
	pos = 0;
	i = -1;
	while (s[++i])
	{
		if ((s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			&& s[i + 1] && s[i + 1] != ' ')
			start = i + 1;
		if (s[i] == 34 || s[i] == 39)
			i = find_next_quote(i + 1, s, s[i]);
		if (s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13)
			&& (s[i + 1] == ' ' || s[i + 1] == '\0'))
		{
			arg[pos] = ft_substr(s, start, i - start + 1);
			if (arg[pos] == NULL)
				exit_error("Malloc failed");
			pos++;
		}
	}
	arg[pos] = NULL;
}

char	**split_words(char *s)
{
	char	**strs;

	strs = malloc_safe(sizeof(char *) * (count_words(s) + 1), 1);
	ft_split_words(s, strs);
	return (strs);
}
