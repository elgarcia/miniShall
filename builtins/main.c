/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:38:31 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/15 15:01:09 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	exe_command(t_paths *paths, char **argv, int argc)
{
	if (ft_strncmp(argv[1], "cd", 3) == 0)
		ft_cd(paths, argv[2]);
	else if (ft_strncmp(argv[1], "echo", 5) == 0)
		ft_echo(argv, argc);
	else if (ft_strncmp(argv[1], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(argv[1], "env", 4) == 0)
		ft_env(paths);
	else if (ft_strncmp(argv[1], "export", 7) == 0)
		ft_export(paths, argv);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;

	new = (t_shell *)ft_calloc(1, sizeof(t_shell));
	new->paths = malloc(sizeof(t_paths));
	new->paths->pwd = ft_strdup(getenv("PWD"));
	new->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
	new->paths->home = ft_strdup(getenv("HOME"));
	fill_init_env_list(new->paths, envp);
	new->paths->export_env_lst = new->paths->env_lst;
	exe_command(new->paths, argv, argc);
	ft_lstclear_env(&new->paths->env_lst);
	free(new->paths->pwd);
	free(new->paths->old_pwd);
	free(new->paths->home);
	free(new->paths);
	free(new);
	return (0);
}
