/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:01:39 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/25 14:32:45 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	init_minishell(t_shell **all, char **envp)
{
	(*all) = (t_shell *)ft_calloc(1, sizeof(t_shell));
	(*all)->n_process = 0;
	(*all)->lst_process = NULL;
	(*all)->input = NULL;
	(*all)->paths = malloc(sizeof(t_paths));
	(*all)->paths->pwd = ft_strdup(getenv("PWD"));
	(*all)->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
	(*all)->paths->home = ft_strdup(getenv("HOME"));
	(*all)->history_path = ft_strjoin((*all)->paths->pwd, "/.history");
	(*all)->og_infile = dup(STDIN_FILENO);
	(*all)->og_outfile = dup(STDOUT_FILENO);
	g_exit_status = 0;
	(*all)->paths->envp = envp;
	fill_init_env_list((*all)->paths, envp);
	(*all)->paths->export_env_lst = duplicate_lst((*all)->paths->env_lst);
}

void	init_pikes(t_shell **all)
{
	(*all)->sons = (pid_t *)ft_calloc((*all)->n_process, sizeof(pid_t));
	(*all)->pipes = (int *)ft_calloc(2, sizeof(int));
	(*all)->fd_in = -1;
	(*all)->fd_out = -1;
}

void	free_pikes(t_shell **all)
{
	free((*all)->sons);
	free((*all)->pipes);
}
