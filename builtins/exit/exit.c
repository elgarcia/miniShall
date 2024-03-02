/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:04 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/02 13:35:02 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"
#include <termios.h>

static int	extend_exit(char *line, int ret_value)
{
	char	**split;
	int		i;
	int		j;

	i = 1;
	split = ft_split(line, ' ');
	while (split[i])
	{
		j = -1;
		while (split[i][++j] != '\0')
		{
			if (!ft_isdigit(split[i][j]))
				return (printf("exit\nMinishell: exit:\
%s: numeric argument required\n", split[i]), 255);
		}
		i++;
	}
	if (arg_counter(split) > 2)
		return (ft_free(split, arg_counter(split)), \
					printf("exit\nbash: exit: too many arguments\n"), 1);
	if (arg_counter(split) > 1)
		ret_value = ft_atoi(split[1]) % 256;
	ft_free(split, arg_counter(split));
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
