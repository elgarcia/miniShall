/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:59:47 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/12 22:23:29 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	char	current_dir[PATH_MAX];
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
		getcwd(current_dir, PATH_MAX);
		resolved_path = resolve_parent_references(current_dir, arg);
		if (!resolved_path)
			return (NULL);
		return (resolved_path);
	}
}

void	update_directory(t_paths *paths, char *new_dir)
{
	update_pwd_variables(paths, new_dir);
	g_exit_status = 0;
}

void	ft_cd(t_paths *paths, char **dir)
{
	char	*new_dir;
	char	tmp[PATH_MAX];

	new_dir = resolve_cd_argument(paths, dir[1]);
	if (arg_counter(dir) == 2 && dir[1][0] == '\0')
	{
		free(new_dir);
		return ;
	}
	if (!new_dir || chdir(new_dir) == -1)
	{
		if (new_dir)
			free(new_dir);
		g_exit_status = 1;
		perror("minishell: cd");
		return ;
	}
	else
		update_directory(paths, new_dir);
	if (dir[1] && !ft_strcmp(dir[1], "-"))
		printf("%s\n", getcwd(tmp, PATH_MAX));
	free(new_dir);
}
