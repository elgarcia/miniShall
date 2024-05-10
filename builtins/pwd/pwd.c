/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:14:06 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 17:38:17 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	buffer[PATH_MAX];

	ft_putendl_fd(getcwd(buffer, PATH_MAX), 1);
	shell->exit_status = 0;
	return (0);
}
