/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:04:04 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/09 21:32:37 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtins_aux2(char **aux, t_shell *all, int len,
		t_process *prc)
{
	if (!ft_strncmp(aux[0], "history", 8))
	{
		execute_builtin(all, prc);
		return (ft_free(&aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "exit", 5))
	{
        ft_free(&aux, len);
		execute_builtin(all, prc);
	}
	ft_free(&aux, len);
	return (0);
}

static int	check_builtins_aux(char **aux, t_shell *all, int len,
		t_process *prc)
{
	if (!ft_strncmp(aux[0], "export", 7))
	{
		execute_builtin(all, prc);
		return (ft_free(&aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "unset", 6))
	{
		execute_builtin(all, prc);
		return (ft_free(&aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "env", 4))
	{
		execute_builtin(all, prc);
		return (ft_free(&aux, len), 1);
	}
	else
		return (check_builtins_aux2(aux, all, len, prc));
	ft_free(&aux, len);
	return (0);
}

int	check_builtins(t_shell *all, t_process *prc)
{
	char	**aux;

	aux = split_words(prc->process);
	remove_quotes_from_matrix(aux);
	if (!ft_strncmp(aux[0], "echo", 5))
	{
		all->exit_status = ft_echo(aux, prc);
		return (ft_free(&aux, arg_counter(aux)), 1);
	}
	else if (!ft_strncmp(aux[0], "cd", 3))
	{
		ft_cd(all->paths, aux);
		return (ft_free(&aux, arg_counter(aux)), 1);
	}
	else if (!ft_strncmp(aux[0], "pwd", 4))
	{
		ft_pwd(all);
		return (ft_free(&aux, arg_counter(aux)), 1);
	}
	return (check_builtins_aux(aux, all, arg_counter(aux), prc));
}

char	*get_ifile(char *process, int inout)
{
	char	**aux;
	char	*ret;
	int		i;

	aux = split_words(process);
	i = inout;
	while (aux[i] && !ft_strncmp(aux[i], "-", 1))
		i++;
	if (aux[i])
	{
		ret = ft_strdup(aux[i]);
        if (!ret)
            exit_error("Malloc failed");
		ft_free(&aux, arg_counter(aux));
		return (ret);
	}
	ft_free(&aux, arg_counter(aux));
	return (NULL);
}

int	check_command(t_shell *all, t_process **prcs, char ***exec_args)
{
	char			**split;
	char			*cmd;
	struct stat		path_stat;

	split = NULL;
	cmd = NULL;
	if (stat((*prcs)->process, &path_stat) == 0 \
	&& (S_ISDIR(path_stat.st_mode)))
		return (printf("%s: is a directory\n", \
		(*prcs)->process), all->exit_status = 126);
	else if ((*prcs)->rd)
	{
		split = split_words((*prcs)->process);
		cmd = get_commad(*prcs, split);
		if ((*prcs)->rd->type == HD && arg_counter(split) == count_rds(*prcs))
			return (all->exit_status);
		all->exit_status = prepare_command(cmd, exec_args, all->paths->env_lst);
		ft_free(&split, arg_counter(split));
	}
	else
		all->exit_status = prepare_command((*prcs)->process, \
		exec_args, all->paths->env_lst);
	if (all->exit_status == -1 || all->exit_status == -2)
		all->exit_status = 127;
	return (all->exit_status);
}
