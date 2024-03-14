/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:07:54 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/09 17:16:50 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_execargs(char ***ex_argc, char *command)
{
	char	**aux;
	int		i;

	i = 0;
	aux = echo_split(command, ' ');
	if (!aux)
		return (-1);
	remove_quotes_from_matrix(aux);
	while (++i < ft_word_count(command, ' '))
	{
		(*ex_argc)[i] = ft_strdup(aux[i]);
		if (!(*ex_argc)[i])
			return (ft_free(ex_argc, i), \
			ft_free(&aux, arg_counter(aux)), -1);
	}
	return (ft_free(&aux, arg_counter(aux)), 0);
}

void	double_free(char **aux, char **actual_path)
{
	free(*actual_path);
	free(*aux);
}
