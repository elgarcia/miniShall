/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:39 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/21 20:34:07 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

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

int has_quotes(char *s)
{
	int 	i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			quotes = s[i];
			while (s[i] && s[i] != quotes)
				i++;
			while (s[i] && s[i] != ' ')
				i++;
			if (s[i] == ' ')
				return (1);
		}
		i++;
	}
	return 0;
}

static int	handle_quoted_word(t_split *params, char quote_type)
{
	int	word_len;

	word_len = quoted_len(&params->s[params->j - 1], quote_type);
	params->strs[params->i] = ft_substr(params->s, params->j - 1, word_len + 1);
	if (!params->strs[params->i])
		return (ft_free(params->strs, params->i), 0);
	(params->j) += word_len;
	(params->i)++;
	return (1);
}

static int handle_unquoted_quoted(t_split *params)
{
	int		word_len;
	int		type;
	int     i;
	
	i = -1;
	type = 0;
	while (params->s[params->j + ++i] && params->s[params->j + i] != ' ')
	{
		if (params->s[params->j + i] == '\"' || params->s[params->j + i] == '\'')
		{
			type = params->s[params->j + i];
			break ;
		}
	}
	if (type)
	{
		//word_len = quoted_len(&params->s[params->j], type);
		//printf("word_len -> %d\n", word_len);
		int	quotes = 0;
		i = -1;
		while (params->s[params->j + ++i])
		{
			if (params->s[params->j + i] == type)
				quotes++;
		}
		quotes /= 2;
		if (quotes % 2)
			word_len = ft_strlen(&params->s[params->j]) - ft_strlen(ft_strrchr(&params->s[params->j], type)) + 1;
		else
			word_len = ft_strlen(&params->s[params->j]) - ft_strlen(ft_strchrt(&params->s[params->j], type, quotes) + quotes);
		//printf("type -> %c\n", type);
		printf("params->s[params->j] -> %s\n", &params->s[params->j]);
		//printf("$quotes -> %d\n", quotes);
		//printf("new word_len -> %d\n", word_len);
		if (word_len == 0)
			return (1);
		params->strs[params->i] = ft_substr(&params->s[params->j], 0, word_len);
		if (!params->strs[params->i])
			return (ft_free(params->strs, params->i), 0);
		(params->j) += word_len;
		(params->i)++;
		return (1);
	}
	return (0);
}

static int	handle_unquoted_word(t_split *params, char c)
{
	int	word_len;
	int	i;

	i = params->j;
	while (params->s[i])
	{
		if (has_quotes(&params->s[i]) && params->i)
		{
			handle_unquoted_quoted(params);
			break;
		}
		i++;
	}
	printf("params->s[params->j] -> %s\n", &params->s[params->j]);
	word_len = len_word(&params->s[params->j], c);
	printf("word_len -> %d\n", word_len);
	params->strs[params->i] = ft_substr(params->s, params->j, word_len);
	if (!params->strs[params->i])
		return (ft_free(params->strs, params->i), 0);
	printf("strs[%d] -> %s\n", params->i, params->strs[params->i]);
	(params->j) += word_len;
	(params->i)++;
	return (1);
}

char	**add_word(t_split *params)
{
	char	*s;
	char	c;
	char	quote_type;

	s = params->s;
	c = params->c;
	printf("before add word -> %s\n", &params->s[params->j]);
	if (is_quoted(s, &(params->j), &quote_type))
	{
		if (!handle_quoted_word(params, quote_type))
			return (NULL);
	}
	else
	{
		if (!handle_unquoted_word(params, c))
			return (NULL);
	}
	return (params->strs);
}
