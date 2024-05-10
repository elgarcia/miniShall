/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:01:39 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/10 16:47:38 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	init_minishell(t_shell **all, char **envp)
{
	char	buffer[PATH_MAX];

	(*all) = (t_shell *)malloc_safe(1, sizeof(t_shell));
	(*all)->n_process = 0;
	(*all)->lst_process = NULL;
	(*all)->input = NULL;
	(*all)->paths = malloc_safe(sizeof(t_paths), 1);
	(*all)->history_path = ft_strjoin(getcwd(buffer, PATH_MAX), "/.history");
	(*all)->og_infile = dup(STDIN_FILENO);
	(*all)->og_outfile = dup(STDOUT_FILENO);
	(*all)->paths->envp = envp;
	fill_init_env_list((*all)->paths, envp, 0);
	(*all)->paths->export_env_lst = duplicate_lst((*all)->paths->env_lst);
	(*all)->exit_status = 0;
	(*all)->paths->shell = (*all);
}

void	init_pikes(t_shell **all)
{
	(*all)->sons = (pid_t *)malloc_safe((*all)->n_process, sizeof(pid_t));
	(*all)->pipes = (int *)malloc_safe(2, sizeof(int));
	(*all)->fd_in = -1;
	(*all)->fd_out = -1;
}

void	free_pikes(t_shell **all)
{
	free((*all)->sons);
	free((*all)->pipes);
}
