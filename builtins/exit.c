/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:04 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/19 09:24:11 by eliagarc         ###   ########.fr       */
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
