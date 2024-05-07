/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:01:39 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/07 18:52:39 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	ft_malloc(char *str, int size)
{
	str = malloc(sizeof(char) * size);
	if (!str)
		exit(-1);
}

void	init_minishell(t_shell **all, char **envp)
{
	char	buffer[PATH_MAX];

	(*all) = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!*all)
		return (exit(0));
	(*all)->n_process = 0;
	(*all)->lst_process = NULL;
	(*all)->input = NULL;
	(*all)->paths = malloc(sizeof(t_paths));
	if (*all)
		return (free(*all), exit(0));
	(*all)->history_path = ft_strjoin(getcwd(buffer, PATH_MAX), "/.history");
		return (free((*all)->paths), free(*all), exit(0));
	(*all)->og_infile = dup(STDIN_FILENO);
	(*all)->og_outfile = dup(STDOUT_FILENO);
	if ((*all)->og_infile == -1 || (*all)->og_outfile == -1)
		return (free((*all)->paths), free(*all), exit(0));
	g_exit_status = 0;
	(*all)->paths->envp = envp;
	fill_init_env_list((*all)->paths, envp, 0);
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
