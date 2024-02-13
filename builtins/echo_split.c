/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/13 13:03:21 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

static char	**allocate_and_initialize(char *s, char c, t_split *params)
{
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * count_words(s, c, 0, 1) + 1);
	if (!strs)
		return (NULL);
	params->s = s;
	params->c = c;
	params->strs = NULL;
	params->i = 0;
	params->j = 0;
	params->in_quotes = 0;
	params->strs = strs;
	return (strs);
}

static void	skip_spaces(t_split *params)
{
	while (params->s[params->j] == ' ')
		params->j++;
}

static void	skip_delimiters(t_split *params)
{
	while ((params->s[params->j] == params->c || params->in_quotes)
		&& params->s[params->j] != '\0')
	{
		if (params->s[params->j] == '\"' || params->s[params->j] == '\'')
			params->in_quotes = !params->in_quotes;
		params->j++;
	}
}

static void	split_string(t_split *params)
{
	while (params->i < count_words(params->s, params->c, 0, 1))
	{
		skip_spaces(params);
		skip_delimiters(params);
		add_word(params);
		if (!params->strs)
			return ;
	}
}

char	**echo_split(char *s, char c)
{
	char	**strs;
	t_split	params;

	strs = allocate_and_initialize(s, c, &params);
	if (!strs)
		return (NULL);
	split_string(&params);
	strs[params.i] = NULL;
	return (strs);
}
