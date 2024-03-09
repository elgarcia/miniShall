/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:01:36 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/09 01:50:30 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pos_rd(char **in, int i, char *rd, int *aux)
{
	int	iter;

	iter = 0;
	while(in[i][iter])
	{
		if (in[i][iter] == rd[0])
		{
			*aux = iter;
			if (iter > 1)
				return (iter);
			break;
		}
		iter++;
	}
	return (0);
}

void	ft_reallocate(char ***in, int size, int pos, char *rd)
{
	int 	og_size;
	char	**aux;
	int		i;
	int		j;
	int		position;

	position = 0;
	i = 0;
	j = 0;
	og_size = arg_counter(*in);
	aux = ft_calloc(og_size + size + 1, sizeof(char *));
	while (i < (og_size + size))
	{
		if (i != pos)
			aux[i++] = ft_strdup((*in)[j++]);
		else
		{
			aux[i++] = ft_substr((*in)[j], 0, pos_rd(*in, j, rd, &position));
			aux[i++] = ft_strdup(rd);
			aux[i++] = ft_substr((*in)[j], position + ft_strlen(rd), ft_strlen((*in)[j]));
			j++;
		}
	}
	aux[i] = NULL;
	ft_free(in, og_size);
	*in = aux;
}

void	separate_rd(char ***input)
{
	int	i;

	i = 0;
	while((*input)[i])
	{
		if (ft_strnstr((*input)[i], "|", ft_strlen((*input)[i])) && ft_strlen((*input)[i]) > 1)
			return (ft_reallocate(input, 2, i, "|"));
		else if (ft_strnstr((*input)[i], "<<", ft_strlen((*input)[i])) && ft_strlen((*input)[i]) > 2)
			return (ft_reallocate(input, 2, i, "<<"));
		else if (ft_strnstr((*input)[i], ">>", ft_strlen((*input)[i])) && ft_strlen((*input)[i]) > 2)
			return (ft_reallocate(input, 2, i, ">>"));
		else if (ft_strnstr((*input)[i], "<", ft_strlen((*input)[i])) && ft_strlen((*input)[i]) > 1)
			return (ft_reallocate(input, 2, i, "<"));
		else if (ft_strnstr((*input)[i], ">", ft_strlen((*input)[i])) && ft_strlen((*input)[i]) > 1)
			return (ft_reallocate(input, 2, i, ">"));
		i++;
	}
}
