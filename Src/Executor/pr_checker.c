/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:04:04 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/09 01:21:41 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prcs(t_shell *all)
{
	t_process	*aux;

	aux = all->lst_process;
	while (aux)
	{
		aux = aux->next;
		free(all->lst_process);
		all->lst_process = aux;
	}
	all->n_process = 0;
	all->lst_process = NULL;
}

static int	check_builtins_aux(char **aux, t_shell *all, \
int len, t_process *prc)
{
	if (!ft_strncmp(aux[0], "export", 7))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_export(all->paths, aux, 1);
		return (ft_free(&aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "unset", 6))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_unset(all->paths, aux);
		return (ft_free(&aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "env", 4))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_env(all->paths, aux);
		return (ft_free(&aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "history", 8))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		print_history(all);
		return (ft_free(&aux, len), 1);
	}
	return (ft_free(&aux, len), 0);
}

int	check_builtins(t_shell *all, t_process *prc)
{
	char	**aux;

	aux = echo_split(prc->process, ' ');
	if (!aux)
		return (printf("echo_split failed!\n"), -1);
	if (!ft_strncmp(aux[0], "echo", 5))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_echo(aux, prc);
		return (ft_free(&aux, arg_counter(aux)), 1);
	}
	else if (!ft_strncmp(aux[0], "cd", 3))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_cd(all->paths, aux);
		return (ft_free(&aux, arg_counter(aux)), 1);
	}
	else if (!ft_strncmp(aux[0], "pwd", 4))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_pwd(all->paths);
		return (ft_free(&aux, arg_counter(aux)), 1);
	}
	return (check_builtins_aux(aux, all, arg_counter(aux), prc));
}

char	*get_ifile(char *process, int inout)
{
	char	**aux;
	char	*ret;
	int		i;

	aux = echo_split(process, ' ');
	i = inout;
	while (aux[i] && !ft_strncmp(aux[i], "-", 1))
		i++;
	if (aux[i])
	{
		ret = ft_strdup(aux[i]);
		ft_free(&aux, ft_word_count(process, ' '));
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
	if (stat((*prcs)->process, &path_stat) == 0)
		return (printf("%s: is a directory\n", (*prcs)->process), g_exit_status = 126);
	else if ((*prcs)->rd)
	{
		split = echo_split((*prcs)->process, ' ');
		cmd = get_commad(*prcs, split);
		if ((*prcs)->rd->type == HD && arg_counter(split) == count_rds(*prcs))
			return (g_exit_status);
		g_exit_status = prepare_command(cmd, exec_args, all->paths->env_lst);
		ft_free(&split, arg_counter(split));
	}
	else
		g_exit_status = prepare_command((*prcs)->process, \
		exec_args, all->paths->env_lst);
	if (g_exit_status == -1 || g_exit_status == -2)
		g_exit_status = 127;
	return (g_exit_status);
}
