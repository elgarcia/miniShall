/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:39 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/14 18:50:57 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

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

static int	has_quotes(char *s)
{
	int		i;
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
		else
			i++;
	}
	return (0);
}

static int	word_utils(t_split *params, int type)
{
	char	*aux;
	int		word_len;

	aux = ft_strchrt(&params->s[params->j], type, 2);
	if (aux && *(aux + 1) && *(aux + 1) != ' ' && *(aux + 1) != '\0')
		aux = ft_strchr(aux, ' ');
	if (!aux)
		word_len = ft_strlen(&params->s[params->j]);
	else
		word_len = ft_strlen(&params->s[params->j]) - ft_strlen(aux) + 1;
	params->strs[params->i] = ft_substr(&params->s[params->j], 0, word_len);
	if (!params->strs[params->i])
		return (ft_free(&params->strs, params->i), 0);
	(params->j) += word_len;
	(params->i)++;
	return (1);
}

static int	handle_quoted_word(t_split *params)
{
	int	type;
	int	i;

	i = -1;
	type = 0;
	while (params->s[params->j + ++i] && params->s[params->j + i] != ' ')
	{
		if (params->s[params->j + i] == '\"' || params->s[params->j
				+ i] == '\'')
		{
			type = params->s[params->j + i];
			break ;
		}
	}
	if (type)
	{
		if (word_utils(params, type))
			return (1);
	}
	return (0);
}

char	**add_word(t_split *params)
{
	int	word_len;
	int	i;

	i = params->j;
	while (params->s[i])
	{
		if (has_quotes(&params->s[i]) && params->i)
		{
			if (handle_quoted_word(params))
				return (params->strs);
		}
		i++;
	}
	word_len = len_word(&params->s[params->j], params->c);
	params->strs[params->i] = ft_substr(params->s, params->j, word_len);
	if (!params->strs[params->i])
		return (ft_free(&params->strs, params->i), NULL);
	(params->j) += word_len;
	(params->i)++;
	return (params->strs);
}
