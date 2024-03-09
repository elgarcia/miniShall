/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_checker_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:24:46 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/09 14:25:08 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_commad(t_process *prc, char **split)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (prc->rd->pos == 0)
	{
		return (ft_substr(prc->process, \
		ft_strlen(split[0]), ft_strlen(prc->process)));
	}
	else
	{
		if (arg_counter(split) > 2)
		{
			ret = ft_strjoin(split[0], " ");
			return (ft_strjoinup(&ret, split[1]));
		}
		else
			return (ft_strdup(split[0]));
	}
}
