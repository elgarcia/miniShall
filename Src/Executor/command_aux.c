/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:07:54 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/22 14:44:48 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_execargs(char ***ex_argc, t_process *command, char *cmd)
{
	char	**aux;
	int		i;
	int		flag;

	i = 0;
	aux = split_words(cmd);
	if (!aux)
		return (-1);
	flag = arg_counter(aux);
	remove_quotes_from_matrix(aux);
	if (command && command->rd)
		flag = flag - 1;
	while (++i < flag)
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
