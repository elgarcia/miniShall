/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:04 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/29 16:08:38 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	ft_exit(t_shell *shell)
{
	free(shell->paths->pwd);
	free(shell->paths->old_pwd);
	free(shell->paths->home);
	free(shell->history_path);
	ft_lstclear_env(&shell->paths->env_lst);
	ft_lstclear_env(&shell->paths->export_env_lst);
	free(shell->paths);
	free(shell);
	exit(EXIT_SUCCESS);
}
