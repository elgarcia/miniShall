#include "../Inc/minishell.h"

void	free_prcs(t_shell *all)
{
	t_process *aux;

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

static int check_builtins_aux(char **aux, t_shell *all, int len)
{
	if (!ft_strncmp(aux[0], "export", 7))
	{
		ft_export(all->paths, aux, 1);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "unset", 6))
	{
		ft_unset(all->paths, aux);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "env", 4))
	{
		ft_env(all->paths, aux);
		return (ft_free(aux, len), 1);
	}
	if (!ft_strncmp(aux[0], "history", 8))
	{
		print_history(all);
		return (ft_free(aux, len), 1);
	}
	return (ft_free(aux, len), 0);
}

int	check_builtins(t_shell *all, char *line)
{
	char	**aux;
	int		len;

	aux = echo_split(line, ' ');
	if (!aux)
		return 1;
	len = arg_counter(aux);
	if (!ft_strncmp(aux[0], "echo", 5))
	{
		ft_echo(all->paths, aux);
		return (ft_free(aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "cd", 3))
	{
		ft_cd(all->paths, aux);
		return (ft_free(aux, len), 1);
	}
	else if (!ft_strncmp(aux[0], "pwd", 4))
	{
		ft_pwd(all->paths);
		return (ft_free(aux, len), 1);
	}
	return (check_builtins_aux(aux, all, len));
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
	ret_val = prepare_command((*prcs)->process, exec_args, all->paths->env_lst);
	if (ret_val == -1 || ret_val == -2)
		g_exit_status = 127;
	return (ret_val);
}
