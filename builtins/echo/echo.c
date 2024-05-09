/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:19 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 17:14:32 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_n(char *token)
{
	int	i;

	if (ft_strncmp(token, "-n", 2))
		return (0);
	i = 2;
	while (token[i])
	{
		if (token[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print(char **argv, int i, t_process *prc)
{
	while (argv[++i])
	{
		if (prc->rd && (i == prc->rd->pos))
			break ;
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	ft_echo(char **argv, t_process *prc)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (argv[i] && check_option_n(argv[i]))
	{
		n_flag = 0;
		i++;
	}
	i--;
	print(argv, i, prc);
	if (n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
