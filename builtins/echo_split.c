/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/12 21:27:52 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

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

static int process_quotes(char const *s, int *i)
{
	char type = s[*i];
	int quote_count = 0;
	while (s[*i] == type && s[*i])
	{
		(*i)++;
		quote_count++;
	}
	while (quote_count)
	{
		if (s[*i] == type)
			quote_count--;
		(*i)++;
	}
	return *i;
}

static int count_words(char const *s, char c)
{
	int counter = 1;
	int i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i = process_quotes(s, &i);
			if (s[i] && (s[i] == '\'' || s[i] == '\"'))
				counter++;
		}
		else
		{
			while (s[i] && s[i] != c)
				i++;
			while (s[i] && s[i] == c)
				i++;
			if (s[i] != c && s[i])
				counter++;
		}
	}
	printf("counter -> %d\n", counter);
	return counter;
}

/*
static int	count_words(char const *s, char c)
{
	int	counter;
	int	i;
	char	type;
	int		quote_count;

	counter = 1;
	i = 0;
	quote_count = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			type = s[i];
			while (s[i] == type && s[i])
			{
				i++;
				quote_count++;
			}
			//printf("quote count -> %d\n", quote_count);
			while (quote_count)
			{
				if (s[i] == type)
					quote_count--;
				i++;
			}
			//printf("quote count -> %d\n", quote_count);
			if (s[i] && s[i] == type)
				counter++;
		}
		else
		{
			while (s[i] && s[i] != c)
				i++;
			while (s[i] && s[i] == c)
				i++;
			if (s[i] != c && s[i])
				counter++;
		}
	}
		printf("counter -> %d\n", counter);
	return (counter);
}
*/

int	quote_count(char *str, char type)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	//printf("type -> %c\n", type);
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] == type)
	{
		counter++;
		i++;
	}
	printf("strchrt count-> %d\n", counter);
	return (counter);
}

static int	quoted_len(char *s, char c)
{
	char	*aux;
	int		len;
	int		len_aux;

	while (*s == ' ')
		s++;
	printf("s -> %s\n", s);
	aux = ft_strchrt(s, c, quote_count(s, c) + quote_count(s, c));
	if (!aux)
		return (ft_strlen(s));
	printf("aux -> %s\n", aux);
	len_aux = ft_strlen(aux);
	printf("len_aux -> %d\n", len_aux);
	printf("s[len_aux] ->  |%c|\n", s[len_aux]);
	if ((s[len_aux]) == '\0')
		len = len_aux;
	else
		len = ft_strlen(s) - len_aux;
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

static int	handle_quoted_word(t_split *params, char quote_type)
{
	int		word_len;

	word_len = quoted_len(&params->s[params->j - 1], quote_type);
	params->strs[params->i] = ft_substr(params->s, params->j - 1, word_len + 1);
	if (!params->strs[params->i])
		return (free_maker(params->strs, params->i), 0);
	(params->j) += word_len;
	(params->i)++;
	return (1);
}

static int	handle_unquoted_word(t_split *params, char c)
{
	int		word_len;

	word_len = len_word(&params->s[params->j], c);
	params->strs[params->i] = ft_substr(params->s, params->j, word_len);
	if (!params->strs[params->i])
		return (free_maker(params->strs, params->i), 0);
	(params->j) += word_len;
	(params->i)++;
	return (1);
}

static char	**add_word(t_split *params)
{
	char	*s;
	char	c;
	char	quote_type;

	s = params->s;
	c = params->c;
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

char	**echo_split(char *s, char c)
{
	char	**strs;
	t_split	params;

	init_struct(&params, s, c);
	if (quotes_counter(s))
	{
		printf("Syntax ERROR!\n");
		return (NULL);
	}
	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * count_words(s, c) + 1);
	if (!strs)
		return (NULL);
	params.strs = strs;
	while (params.i < count_words(s, c))
	{
		while (s[params.j] == ' ')
			params.j++;
		while ((s[params.j] == c || params.in_quotes) && s[params.j] != '\0')
		{
			if (s[params.j] == '\"' || s[params.j] == '\'')
				params.in_quotes = !params.in_quotes;
			params.j++;
		}
		add_word(&params);
		if (!strs)
			return (NULL);
	}
	strs[params.i] = 0;
	return (strs);
}
