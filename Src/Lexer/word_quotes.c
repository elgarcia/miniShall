/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:42:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/30 13:08:50 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	count_words(const char *str)
{
	int			in_quote;
	int			word_count;
	const char	*c;

	in_quote = 0;
	word_count = 0;
	if (!str)
		return (0);
	c = str;
	while (*c)
	{
		if (*c == ' ')
		{
			if (!in_quote)
				word_count++;
		}
		else if (*c == '\"' || *c == '\'')
			in_quote = !in_quote;
		c++;
	}
	if (*str && (str[ft_strlen(str) - 1] != ' ' || in_quote))
		word_count++;
	return (word_count);
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
