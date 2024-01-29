/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:19 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/29 16:31:54 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	ft_expand_variable(char *variable_name, t_paths *paths)
{
	char	*token;

	token = variable_name;
	while (*token)
	{
		if (*token == '$' && *(token + 1) != '\0')
		{
			if (*(token + 1) == '?')
				handle_exit_status(&token);
			else
				handle_variable(&token, paths);
		}
		else
			ft_putchar_fd(*token++, 1);
	}
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

int	is_variable(char *token)
{
	return (token[0] == '$' && token[1] != '\0');
}

void	extend_echo(t_paths *paths, char **argv, int i, int *flag)
{
	char	*variable_name;

	while (argv[i])
	{
		if (argv[i][0] == '\'' || argv[i][0] == '\"')
		{
			if (remove_char(argv[i], argv[i][0]) == 1)
				return ;
		}
		if (is_variable(argv[i]) && *flag != 1)
		{
			variable_name = argv[i];
			ft_expand_variable(variable_name, paths);
		}
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
