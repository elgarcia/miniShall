/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:19 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 16:44:55 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	print_exit_status(t_paths *paths)
{
	ft_putnbr_fd(paths->last_exit_status, 1);
}

int	remove_char(char *str, char c)
{
	int		new;
	int		i;
	int		quotes;

	new = 0;
	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == c)
			quotes++;
		i++;
	}
	i = 0;
	if (quotes % 2 == 0)
	{
		while (str[i])
		{
			if (str[i] && str[i] != c)
				str[new++] = str[i];
			i++;
		}
		str[new] = 0;
	}
	else
	{
		printf("double quotes opened\n");
		return (-1);
	}
	return (1);
}

void	ft_echo_envv(char **argv, t_paths *paths, int i)
{
	char	*value;
	t_env_lst	*tmp;

	if (argv[1][0] == '$' && argv[1][1] == '?')
	{
		print_exit_status(paths);
		return ;
	}
	tmp = find_env_node(paths->env_lst, argv[i]+1);
	if (!tmp)
		return ;
	value = tmp->value;
	ft_putstr_fd(value, 0);
}

int	check_option_n(char *token)
{
	int	i;

	if (ft_strncmp(token, "-n", 2) != 0)
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

void	extend_echo(t_paths *paths, char **argv, int i, int *flag)
{
	while (argv[i])
	{
		if (argv[i][0] == '\'')
			*flag = remove_char(argv[i], '\'');
		else if (argv[i][0] == '\"')
			*flag = remove_char(argv[i], '\"');
		if (*flag == -1)
			return ;
		if (argv[i][0] == '$' && *flag != 1)
			ft_echo_envv(argv, paths, i);
		else
			ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(t_paths *paths, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	//printf("argv-> %s\n", argv[1]);
	while (argv[i] && check_option_n(argv[i]))
	{
		flag = 1;
		i++;
	}
	extend_echo(paths, argv, i, &flag);
	if (flag != 1)
		ft_putchar_fd('\n', 1);
	ft_putchar_fd('\n', 1);
	paths->last_exit_status = 0;
	return (0);
}
