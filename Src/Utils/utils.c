/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:57:33 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/10 18:08:44 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char ***arg, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free((*arg)[i]);
		i++;
	}
	free(*arg);
	*arg = NULL;
}

void	*free_null(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

static void	check_word(const char *s1, size_t *i)
{
	if (s1[*i] == 39)
	{
		while (*i < ft_strlen(s1) && s1[++(*i)] && s1[*i] != 39)
		{
		}
	}
	(*i)++;
}

int	ft_word_count(const char *s1, char delimiter)
{
	int		counter;
	int		aux;
	size_t	i;

	i = 0;
	aux = 0;
	counter = 0;
	if (!s1)
		return (0);
	while (i < ft_strlen(s1))
	{
		while (i < ft_strlen(s1) && s1[i] == delimiter)
		{
			i++;
			aux = 1;
		}
		while (i < ft_strlen(s1) && s1[i] != delimiter)
		{
			check_word(s1, &i);
			aux = 2;
		}
		if (aux == 2)
			counter++;
	}
	return (counter);
}

char	*ft_strjoinup(char **s1, char *s2)
{
	char	*aux;
	int		size_s1;

	if (!(*s1))
	{
		*s1 = (char *)malloc_safe(1, 1);
		if (!(*s1))
			return (NULL);
	}
	size_s1 = ft_strlen(*s1);
	aux = (char *)malloc_safe(size_s1 + ft_strlen(s2) + 1, 1);
	if (!aux)
		return (free_null(s1));
	if (!s2)
		return (free(aux), free_null(s1));
	else
	{
		ft_memcpy(aux, *s1, size_s1 + 1);
		ft_strlcat(aux, s2, size_s1 + ft_strlen(s2) + 1);
	}
	free_null(s1);
	return (aux);
}
