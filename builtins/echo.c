/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:19 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/10 14:58:30 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"

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

	i = 1;
	flag = 0;
	while (argv[i] && argv[i][0] == '1' && argv[i][1] == '2')
	{
		j = 1;
		while (argv[i][j] == '2')
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

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_echo(argv, argc);
	}
	return (0);
}
