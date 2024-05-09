/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 13:00:02 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    strs = malloc(sizeof(char *) * count_words(s) + 1);
	if (!strs)
        exit_error("Malloc failed");
    ft_split_words(s, strs);
	return (strs);
}
