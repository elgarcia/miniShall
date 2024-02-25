/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:42:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 17:06:12 by eliagarc         ###   ########.fr       */
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
	if (s[*i + 1] != type)
	{
		while (s[*i] && s[*i] != ' ')
			(*i)++;
	}
	return (*i);
}

int	count_words(char const *s, char c, int i, int counter)
{
	char	sep;

	sep = c;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = process_quotes(s, &i);
		if (s[i] == sep)
		{
			counter++;
			while (s[i] == sep)
				i++;
		}
		else
			i++;
	}
	return (counter);
}

static int	quote_count(char *str, char type)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] == type)
	{
		counter++;
		i++;
	}
	return (counter);
}

int	quoted_len(char *s, char c)
{
	char	*aux;
	int		len;
	int		len_aux;

	while (*s == ' ')
		s++;
	aux = ft_strchrt(s, c, quote_count(s, c) + quote_count(s, c));
	if (!aux)
		return (ft_strlen(s));
	len_aux = ft_strlen(aux);
	if ((s[len_aux]) == '\0')
		len = len_aux;
	else
		len = ft_strlen(s) - len_aux;
	return (len);
}
