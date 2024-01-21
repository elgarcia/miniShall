#include "../Inc/minishell.h"

void	free_prcs(t_process **pr, t_shell *all)
{
	free(*pr);
	all->n_process -= 1;
	*pr = NULL;
}

static int check_builtins_aux(t_process **prcs, char **aux, t_shell *all, int len)
{
	if (!ft_strncmp(aux[0], "export", 6))
	{
		ft_export(all->paths, aux, 0);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "unset", 5))
	{
		//ft_unset
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "env", 3))
	{
		ft_env(all->paths);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	return (ft_free(aux, len), 0);
}

int	check_builtins(t_process **prcs, t_shell *all)
{
	char	**aux;
	int		len;

	aux = ft_split((*prcs)->process, ' ');
	len = ft_word_count((*prcs)->process, ' ');
	if (!ft_strncmp(aux[0], "echo", 4))
	{
		ft_echo(aux);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "cd", 2))
	{
		ft_cd(all->paths, "~");
		print_env_list(all->paths->env_lst);
		free_prcs(prcs, all);
		return (ft_free(aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "pwd", 3))
	{
		ft_pwd();
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

int	check_command(t_shell *all, t_process **prcs, char ***exec_args, \
int i)
{
	int	ret_val;

	if (all->n_process > 1)
		treat_fork(i, *prcs, exec_args, all);
	else
	{
		ret_val = treat_single((*prcs)->process, exec_args, all->paths->env_lst, all->pipes[i]);
		free_prcs(prcs, all);
		return (ret_val);
	}
	return (0);
}
