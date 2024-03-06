/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:42:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/03 13:24:35 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	count_words(const char *str)
{
	int	word_count;
	int	in_quote;

	if (str == NULL || *str == '\0')
		return (0);
	word_count = 0;
	in_quote = 0;
	while (*str != '\0')
	{
		if (*str == '"')
			in_quote = !in_quote;
		else if (!in_quote && ft_isspace(*str))
			word_count++;
		str++;
	}
	return (word_count + (in_quote || !ft_isspace(*str)));
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
