#include "../Inc/minishell.h"

void	free_prcs(t_process **pr, t_shell *all)
{
	free(*pr);
	all->n_process -= 1;
	*pr = NULL;
}

static int check_builtins_aux(t_process **prcs, char **aux, t_shell *all, int len)
{
	if (!ft_strncmp(aux[0], "export", 7))
	{
		ft_export(all->paths, aux, 1);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "unset", 6))
	{
		ft_unset(all->paths, aux);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "env", 4))
	{
		ft_env(all->paths, aux);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	return (ft_free(aux, len), 0);
}

int	check_builtins(t_process **prcs, t_shell *all, char *line)
{
	char	**aux;
	int		len;

	aux = echo_split(line, ' ');
	len = ft_word_count(line, ' ');
	if (!ft_strncmp(aux[0], "echo", 5))
	{
		ft_echo(all->paths, aux);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "cd", 3))
	{
		ft_cd(all->paths, aux);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "pwd", 4))
	{
		ft_pwd(all->paths);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	return (check_builtins_aux(prcs, aux, all, len));
}

char	*get_ifile(char *process)
{
	char	**aux;
	char	*ret;
	int		i;

	aux = ft_split(process, ' ');
	i = 1;
	while (aux[i] && !ft_strncmp(aux[i], "-", 1))
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
	int	ret_val;

	ret_val = 0;
	if (all->n_process > 1)
	{
		ret_val = treat_fork(*prcs, exec_args, all);
		if (ret_val == -1)
			return (-1);
	}
	else
	{
		ret_val = treat_single((*prcs)->process, exec_args, all->paths->env_lst);
		free_prcs(prcs, all);
		return (ret_val);
	}
	return (ret_val);
}
