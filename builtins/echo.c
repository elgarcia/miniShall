/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:19 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/24 17:16:08 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	print_exit_status(void)
{
	ft_fprintf(1, "%d", g_exit_status);
}

int	quotes_counter(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quotes++;
		else if (str[i] == '\"')
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (1);
	return (0);
}

int	remove_char(char *str, char c)
{
	int	new;
	int	i;

	new = 0;
	i = 0;
	if (!quotes_counter(str))
	{
		while (str[i])
		{
			if (str[i] && str[i] != c)
				str[new ++] = str[i];
			i++;
		}
		str[new] = 0;
	}
	else
	{
		ft_fprintf(2, "Syntax Error!");
		return (1);
	}
	return (0);
}

void	ft_echo_envv(char **argv, t_paths *paths, int i)
{
	char		*value;
	t_env_lst	*tmp;

	if (argv[1][0] == '$' && argv[1][1] == '?')
	{
		print_exit_status();
		return ;
	}
	tmp = find_env_node(paths->env_lst, argv[i] + 1);
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
		if (*flag == 1)
			return ;
		if (argv[i][0] == '$' && *flag != 1)
			// arreglar caso echo $TEST$TEST$TEST=lol$TEST
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
	int	n_flag;

	i = 1;
	flag = 0;
	n_flag = 0;
	while (argv[i] && check_option_n(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	extend_echo(paths, argv, i, &flag);
	if (n_flag == 0)
		ft_putchar_fd('\n', 1);
	g_exit_status = flag;
	return (0);
}
