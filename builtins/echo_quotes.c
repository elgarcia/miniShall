/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:42:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/21 18:59:26 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

static int	process_quotes(char const *s, int *i)
{
	char	type;
	int		quote_count;

	type = s[*i];
	quote_count = 0;
	while (s[*i] && s[*i] == type)
	{
		(*i)++;
		quote_count++;
	}
	while (quote_count)
	{
		if ((!s[*i]))
			return (*i);
		if (s[*i] == type)
			quote_count--;
		(*i)++;
	}
	return (*i);
}

int	count_words(char const *s, char c, int i, int counter)
{
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
	return (counter);
}

static int	quote_count(char *str, char type)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	// printf("type -> %c\n", type);
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] == type)
	{
		counter++;
		i++;
	}
	// printf("strchrt count-> %d\n", counter);
	return (counter);
}

int	quoted_len(char *s, char c)
{
	char	*aux;
	int		len;
	int		len_aux;

	while (*s == ' ')
		s++;
	// printf("s -> %s\n", s);
	aux = ft_strchrt(s, c, quote_count(s, c) + quote_count(s, c));
	if (!aux)
		return (ft_strlen(s));
	// printf("aux -> %s\n", aux);
	len_aux = ft_strlen(aux);
	// printf("len_aux -> %d\n", len_aux);
	// printf("s[len_aux] ->  |%c|\n", s[len_aux]);
	if ((s[len_aux]) == '\0')
		len = len_aux;
	else
		len = ft_strlen(s) - len_aux;
	// printf("len -> %d\n", len);
	return (len);
}
