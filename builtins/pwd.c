/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:14:06 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 22:00:01 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	ft_pwd(t_paths *paths)
{
	ft_putendl_fd(paths->pwd, 0);
	g_exit_status = 0;
	return (0);
}
