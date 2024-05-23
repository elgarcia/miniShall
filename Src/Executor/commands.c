/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:57:51 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/23 19:10:59 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_path(char **env_1, char **actual_path, char *command,
		char ***exec_args)
{
	char	*aux;
	int		i;

	i = -1;
	while (env_1[++i])
	{
		aux = ft_strjoin(env_1[i], "/");
		if (!aux)
			return (-1);
		*actual_path = ft_strjoin(aux, command);
		if (!*actual_path)
			return (free(aux), -1);
		if (access(*actual_path, F_OK | X_OK) == 0)
		{
			(*exec_args)[0] = ft_strdup(*actual_path);
			if (!(*exec_args)[0])
				return (ft_free(exec_args, 1), free(*actual_path), -1);
			return (free(*actual_path), free(aux), 0);
		}
		else
			double_free(&aux, actual_path);
	}
	return (ft_fprintf(2, "%s: command not found\n", command), -2);
}

int	assign_path(char ***exec_args, char *command, t_env_lst *envp)
{
	char		*aux_path;
	t_env_lst	*aux;
	char		**aux2;
	int			flag;

	aux = envp;
	while (aux)
	{
		if (!ft_strncmp(aux->name, "PATH", 4))
		{
			aux2 = ft_split(aux->value, ':');
			if (!aux2)
				return (-1);
			flag = search_path(aux2, &aux_path, command, exec_args);
			return (ft_free(&aux2, ft_word_count(aux->value, ':')), flag);
		}
		aux = aux->next;
	}
	ft_fprintf(2, "%s: No such file or directory\n", command);
	return (-1);
}

int	check_cmd(char **command, char ***exec_args)
{
	if (check_quoted_string(command) == 0)
		remove_quotes_from_string(*command);
	if ((*command)[0] == '.')
	{
		if (access(*command, F_OK | X_OK) == 0)
		{
			(*exec_args)[0] = ft_strdup(*command);
			if (!(*exec_args)[0])
				return (ft_free(exec_args, 1), -1);
			return (0);
		}
		return (perror(*command), -1);
	}
	if (access(*command, F_OK | X_OK) == 0)
	{
		(*exec_args)[0] = ft_strdup(*command);
		if (!(*exec_args)[0])
			return (ft_free(exec_args, 1), -1);
		return (0);
	}
	return (1);
}

static int	init_cmd(int *aux, char ***cmd_split, char *process)
{
	if (!process)
		return (-1);
	*cmd_split = split_words(process);
	if (!*cmd_split || !(*cmd_split)[0])
		return (-1);
	*aux = arg_counter(*cmd_split) + 1;
	return (0);
}

int	prepare_command(char *cmd, char ***exec_args, t_env_lst *envp)
{
	int		aux;
	char	**cmd_split;
	int		path_rt;

	if (init_cmd(&aux, &cmd_split, cmd) == -1)
		return (-1);
	*exec_args = (char **)malloc_safe(aux, sizeof(char *));
	if (!*exec_args)
		return (ft_free(&cmd_split, aux), -1);
	aux = check_cmd(&cmd_split[0], exec_args);
	if (aux == 1)
	{
		path_rt = assign_path(exec_args, cmd_split[0], envp);
		if (path_rt == -1 || path_rt == -2)
		{
			ft_free(&cmd_split, arg_counter(cmd_split));
			return (path_rt);
		}
	}
	if (aux == -1 || init_execargs(exec_args, cmd) == -1)
		return (ft_free(&cmd_split, arg_counter(cmd_split)), -1);
	return (ft_free(&cmd_split, arg_counter(cmd_split)), 0);
}
