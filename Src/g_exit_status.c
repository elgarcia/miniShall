/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_exit_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:40:56 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/01 12:41:33 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	change_status(int new_status)
{
	g_exit_status = new_status;
}
