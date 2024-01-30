/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/30 19:01:21 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

static int	count_words(char const *s, char c)
{
	int	counter;
	int	counter_letters;
	int	i;

	counter = 0;
	i = 0;
	counter_letters = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			counter_letters++;
			i++;
			if (s[i] == '\0' || s[i] == c)
				counter++;
		}
	}
	if (counter_letters > 0 && counter == 0)
		return (1);
	return (counter);
}

static char	**free_maker(char **split, int i)
{
	while (i >= 0)
	{
		free(split[i]);
		--i;
	}
	free(split);
	return (NULL);
}

static int	len_word(char const *s, char c)
{
	int	counter;

	counter = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		counter++;
		s++;
	}
	return (counter);
}

char	**echo_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count_words(s, c))
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		strs[i] = ft_substr(s, j, len_word(&s[j], c));
		if (!strs[i])
			return (free_maker(strs, i));
		j += len_word(&s[j], c);
		i++;
	}
	strs[i] = 0;
	return (strs);
}
