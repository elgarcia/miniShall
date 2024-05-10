/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:36:24 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/10 16:53:12 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_synerr(t_shell **all, int i)
{
	if (there_is_rd((*all)->lst_process) || is_ao((*all)->input[i - 1]))
	{
		ft_fprintf(2, "Syntax error\n");
		free_prcs(all);
		g_exit_status = 258;
		return (ft_free(&(*all)->input, arg_counter((*all)->input)), -1);
	}
	return (0);
}
