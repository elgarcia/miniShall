/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:59:47 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/04 15:51:42 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"
#include <sys/stat.h>

char	*new_path(t_paths *paths, char *arg)
{
	char	*result;
	char	*tmp;

	if (!arg || arg[0] == '\0' || !ft_strcmp(arg, "~"))
		return (get_env("HOME", paths->env_lst));
	else if (!ft_strncmp(arg, "~/", 2))
	{
		tmp = ft_strchr(arg, '/');
		result = ft_strjoinfree(get_env("HOME", paths->env_lst), tmp);
		return (result);
	}
	return (NULL);
}

char	*resolve_cd_argument(t_paths *paths, char *arg)
{
	char	*current_dir;
	char	*resolved_path;
	char	tmp[PATH_MAX];

	if (!arg || arg[0] == '\0' || !ft_strncmp(arg, "~", 1))
		return (new_path(paths, arg));
	else if (!ft_strncmp(arg, "/", 1))
		return (ft_strdup(arg));
	else if (!ft_strcmp(arg, ".."))
		return (get_previous_dir(getcwd(tmp, PATH_MAX)));
	else if (!ft_strcmp(arg, "."))
		return (getcwd(NULL, 0));
	else if (!ft_strcmp(arg, "-"))
		return (get_env("OLDPWD", paths->env_lst));
	else
	{
		current_dir = getcwd(NULL, 0);
		resolved_path = resolve_parent_references(current_dir, arg);
		free(current_dir);
		if (!resolved_path)
			return (NULL);
		return (resolved_path);
	}
}

void	handle_too_many_arguments(void)
{
	ft_fprintf(2, "cd: Too many arguments\n");
	g_exit_status = 1;
}

void	update_directory(t_paths *paths, char *new_dir)
{
	update_pwd_variables(paths, new_dir);
	g_exit_status = 0;
}

void	ft_cd(t_paths *paths, char **dir)
{
	char	*new_dir;
	int		argc;
	char	tmp[PATH_MAX];

	argc = arg_counter(dir);
	if (argc > 2)
	{
		handle_too_many_arguments();
		return ;
	}
	new_dir = resolve_cd_argument(paths, dir[1]);
	if (!new_dir || chdir(new_dir) == -1)
	{
		g_exit_status = 1;
		perror("minishell: cd");
	}
	else
		update_directory(paths, new_dir);
	if (dir[1] && !ft_strcmp(dir[1], "-"))
		printf("%s\n", getcwd(tmp, PATH_MAX));
	free(new_dir);
}
