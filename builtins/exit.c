/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:04 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/19 11:02:42 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	ft_exit(t_shell *shell, char *line)
{
	char **split;
	int ret_value;

	ret_value = 0;
	if (line)
	{
		split = ft_split(line, ' ');
		if (arg_counter(split) > 2)
		{
			printf("exit\nexit: too many arguments\n");
			return ;
		}
		if (arg_counter(split) > 1)
			ret_value = ft_atoi(split[1]);
	}
	free(shell->paths->pwd);
	free(shell->paths->old_pwd);
	free(shell->paths->home);
	free(shell->history_path);
	ft_lstclear_env(&shell->paths->env_lst);
	ft_lstclear_env(&shell->paths->export_env_lst);
	free(shell->paths);
	free(shell);
	exit(ret_value);
}
