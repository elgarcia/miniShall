/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:38:31 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/15 11:20:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/built_ins.h"

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
}

int	main(int argc, char **argv, char **envp)
{
	t_paths paths;

	paths.pwd = ft_strdup(getenv("PWD"));
	paths.old_pwd = ft_strdup(getenv("OLDPWD"));
	paths.home = getenv("HOME");
	fill_init_env_list(&paths, envp);
	exe_command(&paths, argv, argc);
	ft_lstclear_env(&paths.env_lst);
	return (0);
}
