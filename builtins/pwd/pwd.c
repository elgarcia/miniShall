/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:14:06 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/02 13:31:17 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	ft_pwd(void)
{
	char	buffer[PATH_MAX];

	ft_putendl_fd(getcwd(buffer, PATH_MAX), 1);
	g_exit_status = 0;
	return (0);
}
