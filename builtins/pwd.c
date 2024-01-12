/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:14:06 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/12 14:56:49 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

int	find_pwd(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PWD=", 4) != 0)
		i++;
	return (i);
}

int	ft_pwd(char **envp)
{
	ft_putendl_fd(envp[find_pwd(envp)] + 4, 1);
	return (0);
}

int	ft_pwd2(void)
{
	ft_putendl_fd(getenv("PWD"), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	ft_pwd2();
	return (0);
}
