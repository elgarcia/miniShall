/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:01:36 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/10 13:39:56 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pos_rd(char **in, int i, char *rd, int *aux)
{
	int	iter;

	iter = 0;
	if ((in[i][0] == '\"' || in[i][0] == '\''))
		iter = skip_quotes(in[i], 0, in[i][0]);
	*aux = iter;
	while (in[i][iter])
	{
		if (ft_strlen(rd) == 1)
		{
			if (in[i][iter] == rd[0])
				*aux = iter;
		}
		else
		{
			if (in[i][iter] == rd[0] && in[i][iter + 1] && \
			in[i][iter + 1] == rd[1])
				*aux = iter;
		}
		iter++;
	}
	return (*aux);
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

static void	separate_rd_aux(char ***input, int *i, int aux)
{
	if (ft_strnstr((*input)[*i] + aux, "|", ft_strlen((*input)[*i] + aux)) \
	&& ft_strcmp((*input)[*i] + aux, "|"))
	{
		if (ft_strcmp((*input)[*i] + aux, "||"))
		{
			*input = ft_reallocate(input, 2, *i, "|");
			(*i)--;
		}
	}
	else if (ft_strnstr((*input)[*i] + aux, "<", \
	ft_strlen((*input)[*i] + aux)) && (ft_strncmp((*input)[*i] + aux, "<", 2) \
	&& ft_strcmp((*input)[*i] + aux, "<<")))
	{
		*input = ft_reallocate(input, 2, *i, "<");
		(*i)--;
	}
	else if (ft_strnstr((*input)[*i] + aux, ">", \
	ft_strlen((*input)[*i] + aux)) && ft_strncmp((*input)[*i] + aux, ">", 2) \
	&& ft_strcmp((*input)[*i] + aux, ">>"))
	{
		*input = ft_reallocate(input, 2, *i, ">");
		(*i)--;
	}
}

int	separate_rd(char ***input, int i)
{
	int	aux;

	while ((*input)[++i])
	{
		aux = 0;
		if (((*input)[i][0] == '\"' || (*input)[i][0] == '\''))
			aux = skip_quotes((*input)[i], 0, (*input)[i][0]);
		if (aux == -1)
			return (ft_fprintf(2, "Quotes Opened!\n"), -1);
		if (ft_strnstr((*input)[i] + aux, "<<", ft_strlen((*input)[i] + aux)) \
		&& (ft_strcmp((*input)[i] + aux, "<<")))
		{
			*input = ft_reallocate(input, 2, i, "<<");
			i--;
		}
		else if (ft_strnstr((*input)[i] + aux, ">>", \
		ft_strlen((*input)[i] + aux)) && (ft_strcmp((*input)[i] + aux, ">>")))
		{
			*input = ft_reallocate(input, 2, i, ">>");
			i--;
		}
		else
			separate_rd_aux(input, &i, aux);
	}
	return (0);
}
