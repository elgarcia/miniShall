/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/03 13:36:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static char	**allocate_and_initialize(char *s, char c, t_split *params)
{
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * (count_words(s) + 1));
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
	while (params->i < count_words(params->s))
	{
		while (params->s[params->j] == ' ')
			params->j++;
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
	int		i;
	char	*tmp;

	i = 0;
	strs = allocate_and_initialize(s, c, &params);
	if (!strs)
		return (NULL);
	split_string(&params);
	strs[params.i] = 0;
	while (strs[i])
	{
		tmp = ft_strtrim(strs[i], " ");
		free(strs[i]);
		strs[i] = tmp;
		i++;
	}
	return (strs);
}
