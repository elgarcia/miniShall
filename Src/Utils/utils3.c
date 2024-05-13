/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:07:10 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/13 15:34:30 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*malloc_safe(int num_elements, int size)
{
	void	*mem;

	mem = ft_calloc(num_elements, size);
	if (!mem)
		exit_error("malloc_safe failed");
	return (mem);
}
