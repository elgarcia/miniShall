/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:04:04 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/12 21:37:53 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

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

static int	check_builtins_aux(char **aux, t_shell *all, int len, t_process *prc)
{
	if (!ft_strncmp(aux[0], "export", 7))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_export(all->paths, aux, 1);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "unset", 6))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_unset(all->paths, aux);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "env", 4))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_env(all->paths, aux);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "history", 8))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		print_history(all);
		return (ft_free(aux, len), 1);
	}
	return (ft_free(aux, len), 0);
}

int	check_builtins(t_shell *all, char *line, t_process *prc)
{
	char	**aux;

	aux = echo_split(line, ' ');
	if (!aux[0])
		return (1);
	if (!ft_strncmp(aux[0], "echo", 5))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_echo(all->paths, aux);
		return (ft_free(aux, arg_counter(aux)), 1);
	}
	else if (!ft_strncmp(aux[0], "cd", 3))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_cd(all->paths, aux);
		return (ft_free(aux, arg_counter(aux)), 1);
	}
	else if (!ft_strncmp(aux[0], "pwd", 4))
	{
		exec_type(all, prc, ft_word_count(prc->process, ' '));
		ft_pwd(all->paths);
		return (ft_free(aux, arg_counter(aux)), 1);
	}
	return (check_builtins_aux(aux, all, arg_counter(aux), prc));
}

char	*get_ifile(char *process, int inout)
{
	char	**aux;
	char	*ret;
	int		i;

	aux = ft_split(process, ' ');
	i = inout;
	while (aux[i] && !ft_strncmp(aux[i], "-", 2))
		i++;
	if (aux[i])
	{
		ret = ft_strdup(aux[i]);
		ft_free(aux, ft_word_count(process, ' '));
		return (ret);
	}
	ft_free(aux, ft_word_count(process, ' '));
	return (NULL);
}

int	check_command(t_shell *all, t_process **prcs, char ***exec_args)
{
	int		ret_val;
	char	**split;

	split = NULL;
	ret_val = 0;
	if ((*prcs)->rd)
	{
		split = ft_split((*prcs)->process, ' ');
		ret_val = prepare_command(split[0], exec_args, all->paths->env_lst);
		ft_free(split, arg_counter(split));
	}
	else
		ret_val = prepare_command((*prcs)->process, \
		exec_args, all->paths->env_lst);
	if (ret_val == -1 || ret_val == -2)
		g_exit_status = 127;
	return (ret_val);
}
