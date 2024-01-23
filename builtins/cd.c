/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:59:47 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 21:46:36 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"
#include <sys/stat.h>

char	*join_paths(const char *path1, const char *path2)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin(path1, "/");
	tmp = ft_strjoin(result, path2);
	free(result);
	return (tmp);
}

char	*get_previous_dir(char *str)
{
	int		i;
	char	*new;
	char	*aux;

	aux = ft_strrchr(str, '/');
	i = (aux - str);
	new = ft_substr(str, 0, i);
	if (!new[0])
		new = ft_strdup("/");
	return (new);
}

char	*get_full_path(char *current_dir, char *target)
{
	return (join_paths(current_dir, target));
}

char	*resolve_cd_argument(t_paths *paths, char *arg)
{
	char	*current_dir;
	char	*resolved_path;

	if (!arg || !ft_strcmp(arg, "~"))
		return (ft_strdup(paths->home));
	else if (!ft_strcmp(arg, "/"))
		return (ft_strdup(arg));
	else if (!ft_strcmp(arg, ".."))
		return (get_previous_dir(paths->pwd));
	else if (!ft_strcmp(arg, "."))
		return (NULL);
	else if (!ft_strcmp(arg, "-"))
		return (ft_strdup(paths->old_pwd));
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
	ft_putendl_fd("cd: Too many arguments", 2);
	g_exit_status = 1;
}

void	handle_cd_error(void)
{
	g_exit_status = 1;
	perror("cd");
}

void	update_directory(t_paths *paths, char *new_dir)
{
	if (chdir(new_dir) != 0)
		handle_cd_error();
	else
	{
		update_pwd_variables(paths, new_dir);
		g_exit_status = 0;
	}
}

void	ft_cd(t_paths *paths, char **dir)
{
	char	*new_dir;
	int		argc;

	argc = arg_counter(dir);
	if (argc > 2)
	{
		handle_too_many_arguments();
		return ;
	}
	new_dir = resolve_cd_argument(paths, dir[1]);
	if (!new_dir || chdir(new_dir) != 0)
		handle_cd_error();
	else
		update_directory(paths, new_dir);
	free(new_dir);
}
