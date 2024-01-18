/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:14:06 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/15 12:01:37 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	find_pwd(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PWD=", 4) != 0)
		i++;
	return (i);
}

int	ft_pwd2(char **envp)
{
	ft_putendl_fd(envp[find_pwd(envp)] + 4, 1);
	return (0);
}

int	ft_pwd(void)
{
	ft_putendl_fd(getenv("PWD"), 1);
	return (0);
}
