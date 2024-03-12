/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:04 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/12 13:27:48 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"
#include <termios.h>

static void    check_num(char **split)
{
    int i;
    int j;

    i = 1;
    if (split[i][0] == '\0')
    {
        ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", split[i]);
        ft_free(&split, arg_counter(split));
        exit(255);
    }
    while (split[i])
    {
        j = 0;
        if ((split[i][j] == '-' || split[i][j] == '+') && !ft_isdigit(split[i][j + 1]))
            j++;
        while (split[i][j])
        {
            if (!ft_isdigit(split[i][j]) || split[i][0] == '\0')
            {
                ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", split[i]);
                ft_free(&split, arg_counter(split));
                exit(255);
            }
            j++;
        }
        i++;
    }
}

static int	extend_exit(char *line, int ret_value)
{
	char	**split;

    split = echo_split(line, ' ');
    if (!split)
        return (ret_value);
    if (arg_counter(split) == 1)
    {
        ft_free(&split, arg_counter(split));
        return (ret_value);
    }
    if (arg_counter(split) > 2)
    {
        ft_fprintf(2, "exit\nminishell: exit: too many arguments\n");
        ft_free(&split, arg_counter(split));
        return (1);
    }
    remove_quotes_from_matrix(split);
    check_num(split);
	if (arg_counter(split) > 1)
		ret_value = ft_atoi(split[1]) % 256;
	ft_free(&split, arg_counter(split));
	return (ret_value);
}

void	ft_exit(t_shell *shell, char *line)
{
	int				ret_value;
	struct termios	term;

	ret_value = 0;
	if (line)
		ret_value = extend_exit(line, 0);
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
