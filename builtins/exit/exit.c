/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:04 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/13 11:50:44 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"
#include <termios.h>

int	static	ft_atoi_error(int *error)
{
	*error = 1;
	return (-1);
}

long long	static	ft_atol(const char *str, int *atoi_error)
{
	int			i;
	int			sign;
	long long	nbr;

	nbr = 0;
	i = 0;
	sign = 1;
	if (ft_strlen(str) == 19
		&& (ft_strncmp("9223372036854775807", str, 20) < 0))
		return (ft_atoi_error(atoi_error));
	if ((ft_strlen(str) == 20 && ft_strncmp
			("-9223372036854775807", str, 21) < 0) || ft_strlen(str) > 20)
		return (ft_atoi_error(atoi_error));
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

static void    check_num(char **split)
{
    int i;
    int j;

    i = 1;
    if (split[i][0] == '\0')
    {
        ft_fprintf(2, "exit\nminishell: exit: %s\
: numeric argument required\n", split[i]);
        ft_free(&split, arg_counter(split));
        exit(255);
    }
    while (split[i])
    {
        j = 0;
        if ((split[i][j] == '-' || split[i][j] == '+'))
            j++;
        while (split[i][j])
        {
            if (!ft_isdigit(split[i][j]) || split[i][0] == '\0')
            {
                ft_fprintf(2, "exit\nminishell: exit: %s\
: numeric argument required\n", split[i]);
                ft_free(&split, arg_counter(split));
                exit(255);
            }
            j++;
        }
        i++;
    }
}

static long long	extend_exit(char **split, int ret_value)
{
	int		i;
	long long ret;

	i = 0;
    if (!split)
        return (ret_value);
    if (arg_counter(split) == 1)
    {
        ft_free(&split, arg_counter(split));
        return (ret_value);
    }
    remove_quotes_from_matrix(split);
    check_num(split);
	ret = ft_atol(split[1], &i);
	if (i == 1)
	{
		ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n",
			split[1]);
		ft_free(&split, arg_counter(split));
		exit(255);
	}
	if (arg_counter(split) == 2)
		ret_value = ft_atoi(split[1]) % 256;
	ft_free(&split, arg_counter(split));
	return (ret);
}

void	ft_exit(t_shell *shell, char *line)
{
	int				ret_value;
	struct termios	term;
	char			**split;

	ret_value = 0;
	split = ft_split(line, ' ');
	if (arg_counter(split) > 2)
	{
		ft_fprintf(2, "exit\nminishell: exit: too many arguments\n");
		ft_free(&split, arg_counter(split));
		return ;
	}
	if (line)
		ret_value = extend_exit(split, 0);
	free(shell->history_path);
	ft_lstclear_env(&shell->paths->env_lst);
	ft_lstclear_env(&shell->paths->export_env_lst);
	free(shell->paths);
	free(shell);
	tcgetattr(0, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	exit(ret_value);
}
