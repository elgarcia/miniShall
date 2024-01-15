/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:19 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/15 12:01:27 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

static void	extend_echo(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] && argv[i][0])
			write(1, " ", 1);
		i++;
	}
}

int	ft_echo(char **argv, int argc)
{
	int	i;
	int	j;
	int	flag;

	i = 2; // ahora funciona con el argv[2], al tener el minishell cambiarlo a 1 o 0
	flag = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == '\0')
			flag = 1;
		else
			break ;
		i++;
	}
	extend_echo(argv, i);
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
