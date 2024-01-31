/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/31 15:40:33 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Inc/minishell.h"

typedef struct s_split
{
	char	*s;
	char	c;
	char	**strs;
	int		i;
	int		j;
	int		in_quotes;
}			t_split;

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

static int	count_words(char const *s, char c)
{
	int	counter;
	int	in_quotes;
	int	i;
	char	type;

	counter = 0;
	in_quotes = 0;
	i = 0;
	if (s[i] == '\"' || s[i] == '\'')
	{
		type = s[i];
		while (s[i] != '\0')
		{
			while (s[i] == type)
				i++;
			if (s[i] != type && s[i])
			{
				counter++;
				while (s[i] != type)
					i++;
				break ;
			}
		}
	}
	else
	{
		while (s[i] != '\0')
		{
			while (s[i] == c)
				i++;
			while (s[i] != c && s[i])
			{
				i++;
				if (s[i] == '\0' || s[i] == c)
					counter++;
			}
		}
	}
	printf ("count words -> %d\n", counter);
	return (counter);
}

int	quote_count(char *str, char type)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == type)
			counter++;
		i++;
	}
	return (counter);
}

static int	quoted_len(char *s, char c)
{
	char	*aux;
	int		len;
	char	*cpy;

	cpy = s;
	while (*s == ' ')
		s++;
	aux = ft_strchrt(s, c, quote_count(s, c));
	printf("aux -> %s\n", aux);
	if (!aux)
		return (0);
	len = ft_strlen(cpy) - ft_strlen(aux) + 1;
	printf("len -> %d\n", len);
	return (len);
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

void	init_struct(t_split *split, char *str, char c)
{
	split->s = str;
	split->c = c;
	split->strs = NULL;
	split->i = 0;
	split->j = 0;
	split->in_quotes = 0;
}

static int	is_quoted(char const *s, int *j, char *quote_type)
{
	if (s[*j] == '\"' || s[*j] == '\'')
	{
		*quote_type = s[*j];
		(*j)++;
		return (1);
	}
	return (0);
}

static char	**add_word(t_split *params)
{
	char	*s;
	char	c;
	char	quote_type;
	int		word_len;

	s = params->s;
	c = params->c;
	if (is_quoted(s, &(params->j), &quote_type))
	{
		word_len = quoted_len(&s[params->j], quote_type);
		params->strs[params->i] = ft_substr(s, params->j - 1, word_len + 1);
		if (!params->strs[params->i])
			return (free_maker(params->strs, params->i));
		(params->j) += word_len;
		(params->i)++;
	}
	else
	{
		word_len = len_word(&s[params->j], c);
		params->strs[params->i] = ft_substr(s, params->j, word_len);
		if (!params->strs[params->i])
			return (free_maker(params->strs, params->i));
		(params->j) += word_len;
		(params->i)++;
	}
	return (params->strs);
}

char	**echo_split(char *s, char c)
{
	char	**strs;
	t_split	params;

	init_struct(&params, s, c);
	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * count_words(s, c) + 1);
	if (!strs)
		return (NULL);
	params.strs = strs;
	while (params.i < count_words(s, c))
	{
		while ((s[params.j] == c || params.in_quotes) && s[params.j] != '\0')
		{
			if (s[params.j] == '\"' || s[params.j] == '\'')
				params.in_quotes = !params.in_quotes;
			params.j++;
			if (s[params.j] == ' ')
				params.i++;
		}
		add_word(&params);
		if (!strs)
			return (NULL);
	}
	strs[params.i] = 0;
	return (strs);
}
