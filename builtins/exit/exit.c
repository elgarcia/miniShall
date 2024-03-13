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

static int    check_num(char **split)
{
    int i;
    int j;

    i = 1;
    if (split[i][0] == '\0')
    {
        ft_fprintf(2, "exit\nminishell: exit: %s\
: numeric argument required\n", split[i]);
        ft_free(&split, arg_counter(split));
        return (1);
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
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

void    clear_everything(t_shell *shell)
{
	struct termios	term;

    free(shell->history_path);
    ft_lstclear_env(&shell->paths->env_lst);
    ft_lstclear_env(&shell->paths->export_env_lst);
    free(shell->paths);
    free(shell);
	tcgetattr(0, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

void	ft_exit(t_shell *shell, char *line)
{
	int				ret_value;
	char			**split;

	ret_value = 0;
	split = ft_split(line, ' ');
	if (arg_counter(split) > 2)
	{
		ft_fprintf(2, "exit\nminishell: exit: too many arguments\n");
        g_exit_status = 1;
		ft_free(&split, arg_counter(split));
		return ;
	}
    if (split[1])
    {
        ret_value = ft_atoi(split[1]);
        if (check_num(split))
            ret_value = 255;
    }
    else
        ft_free(&split, arg_counter(split));
    clear_everything(shell);
	exit(ret_value);
}
