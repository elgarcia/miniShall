/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:04 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/17 03:20:14 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

int	max_exit_nb(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	i = ft_isspace(str);
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result * sign > (LLONG_MAX - (str[i] - '0')) / 10 || result
			* sign < (LLONG_MIN + (str[i] - '0')) / 10)
			return (-1);
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && ft_isspace(str + i) == 0)
		return (-1);
	return (0);
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	clear_everything(t_shell *shell, int pikes)
{
	struct termios	term;

	if (shell->history_path)
		free(shell->history_path);
	ft_lstclear_env(&shell->paths->env_lst);
	ft_lstclear_env(&shell->paths->export_env_lst);
	ft_lstclear_pro(&shell->lst_process);
	if (pikes)
		free_pikes(&shell);
	if (shell->paths)
		free(shell->paths);
	if (shell)
		free(shell);
	tcgetattr(0, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	unlink(".temp.txt");
}

void	print_exit_error(char **split, t_shell *shell)
{
	ft_fprintf(2, "exit\nminishell:\
 exit: %s: numeric argument required\n", split[1]);
	ft_free(&split, arg_counter(split));
	clear_everything(shell, 1);
	exit(255);
}

void	ft_exit(t_shell *shell, char *line)
{
	int		ret_value;
	char	**split;

	ret_value = shell->exit_status;
	split = split_words(line);
	remove_quotes_from_matrix(split);
	if (split[1])
	{
		ret_value = ft_atoi(split[1]);
		if (check_num(split[1]) || max_exit_nb(split[1]) != 0)
			print_exit_error(split, shell);
	}
	if (arg_counter(split) > 2)
	{
		ft_fprintf(2, "exit\nminishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return ((void)ft_free(&split, arg_counter(split)));
	}
	if (!shell->pipes[0])
		printf("exit\n");
	ft_free(&split, arg_counter(split));
	clear_everything(shell, 1);
	exit(ret_value);
}
