/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/20 12:37:24 by bautrodr         ###   ########.fr       */
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

char	*ft_strtrimfree(char *s1, char const *set)
{
	char	*str;
	size_t	j;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	j = ft_strlen(s1);
	while (j && ft_strchr(set, s1[j]))
		j--;
	str = ft_substr(s1, 0, j + 1);
	if (!str)
		return (NULL);
	free(s1);
	return (str);
}

char	**echo_split(char *s, char c)
{
	char	**strs;
	t_split	params;
	int		i;
	static int times = 0;

	//printf("time -> %d string -> %s\n", times, s);
	strs = allocate_and_initialize(s, c, &params);
	if (!strs)
		return (NULL);
	split_string(&params);
	strs[params.i] = 0;
	i = 0;
	while (strs[i]) // last change 17-02 at home
	{
		strs[i] = ft_strtrimfree(strs[i], " ");
		//if (strs[i][0] == '\'' || strs[i][0] == '\"')
		//	remove_char(strs[i], strs[i][0]);
		i++;
	}
	//for (int j = 0; strs[j]; j++)
	//	printf("strs[%d] -> %s\n", j, strs[j]);
	times++;
	return (strs);
}
