/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:01:36 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/14 18:52:31 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pos_rd(char **in, int i, char *rd, int *aux)
{
	int	iter;

	iter = 0;
	while (in[i][iter])
	{
		if (in[i][iter] == rd[0])
		{
			*aux = iter;
			return (iter);
		}
		iter++;
	}
	return (0);
}

static void	ft_allocate(int comp, int *size, char ***aux, size_t len)
{
	if (comp != 0 && comp != (int)len)
		*aux = ft_calloc(*size + 1, sizeof(char *));
	else
		*aux = ft_calloc(--(*size) + 1, sizeof(char *));
}

static int	init_reallocate(int *position, int *i, int *j, int size)
{
	*position = 0;
	*i = 0;
	*j = 0;
	return (size);
}

char	**ft_reallocate(char ***in, int size, int pos, char *rd)
{
	int		og_size;
	char	**aux;
	int		i;
	int		j;
	int		index;

	og_size = init_reallocate(&index, &i, &j, arg_counter(*in) + size);
	ft_allocate(pos_rd(*in, pos, rd, &index), \
	&og_size, &aux, ft_strlen((*in)[pos]) - 1);
	while (i < og_size)
	{
		if (i != pos)
			aux[i++] = ft_strdup((*in)[j++]);
		else
		{
			if (index != 0)
				aux[i++] = ft_substr((*in)[j], 0, index);
			aux[i++] = ft_strdup(rd);
			if (index != (int)ft_strlen((*in)[pos]) - 1)
				aux[i++] = ft_substr((*in)[j], \
				index + ft_strlen(rd), ft_strlen((*in)[j]));
			j++;
		}
	}
	return (ft_free(in, arg_counter(*in)), aux);
}

void	separate_rd(char ***input)
{
	int	i;
	int	aux;

	i = -1;
	while ((*input)[++i])
	{
		aux = 0;
		if (i != 0 && ((*input)[i][0] == '\"' || (*input)[i][0] == '\''))
			aux = skip_quotes((*input)[i]);
		if (ft_strnstr((*input)[i] + aux, "|", ft_strlen((*input)[i] + aux)) \
		&& ft_strcmp((*input)[i], "|"))
			*input = ft_reallocate(input, 2, i, "|");
		else if (ft_strnstr((*input)[i] + aux, "<<", \
		ft_strlen((*input)[i] + aux)) && ft_strcmp((*input)[i], "<<"))
			*input = ft_reallocate(input, 2, i, "<<");
		else if (ft_strnstr((*input)[i] + aux, ">>", \
		ft_strlen((*input)[i] + aux)) && ft_strcmp((*input)[i], ">>"))
			*input = ft_reallocate(input, 2, i, ">>");
		else if (ft_strnstr((*input)[i] + aux, "<", \
		ft_strlen((*input)[i] + aux)) && ft_strncmp((*input)[i], "<", 2))
			*input = ft_reallocate(input, 2, i, "<");
		else if (ft_strnstr((*input)[i] + aux, ">", \
		ft_strlen((*input)[i] + aux)) && ft_strncmp((*input)[i], ">", 2))
			*input = ft_reallocate(input, 2, i, ">");
	}
}
