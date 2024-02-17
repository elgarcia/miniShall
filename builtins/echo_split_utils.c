/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:22:36 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/17 17:11:34 by bautrodr         ###   ########.fr       */
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

static int	handle_unquoted_word(t_split *params, char c)
{
	int	word_len;

	word_len = len_word(&params->s[params->j], c);
	params->strs[params->i] = ft_substr(params->s, params->j, word_len);
	if (!params->strs[params->i])
		return (ft_free(params->strs, params->i), 0);
	(params->j) += word_len;
	(params->i)++;
	return (1);
}
/*   NOT FINISHED
static int handle_unquoted_quoted(t_split *params)
{
	int		word_len;
	int		type;
	char	*tmp;

	type = 0;
	tmp = ft_strdup(&params->s[params->j]);
	for (int i = 0; tmp[i]; i++)
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			type = tmp[i];
			break;
		}
	}
	if (type)
	{
		//printf("&params->s[params->j] -> %s\n", &params->s[params->j]);
		word_len = quoted_len(&params->s[params->j], type);
		//printf("word_len -> %d\n", word_len);
		params->strs[params->i] = ft_substr(&params->s[params->j], 0, word_len);
		if (!params->strs[params->i])
			return (ft_free(params->strs, params->i), 0);
		printf("params[i]--> |%s|\n", params->strs[params->i]);
		(params->j) += word_len;
		(params->i)++;
		free(tmp);
		return (1);
	}
	free(tmp);
	return 0;
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return 1;
		i++;
	}
	return (0);
}
*/
char	**add_word(t_split *params)
{
	char	*s;
	char	c;
	char	quote_type;

	s = params->s;
	c = params->c;
	//printf("before add word -> %s\n", &params->s[params->j]);
	if (is_quoted(s, &(params->j), &quote_type))
	{
		if (!handle_quoted_word(params, quote_type))
			return (NULL);
	}
	else
	{
		//if (has_quotes(&params->s[params->j]))
		//{
		//	handle_unquoted_quoted(params);
		//	return (params->strs);
		//}
		if (!handle_unquoted_word(params, c))
			return (NULL);
	}
	return (params->strs);
}
