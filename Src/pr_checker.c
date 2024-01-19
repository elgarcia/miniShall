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
	int		i;

	aux = ft_split(process, ' ');
	i = 1;
	while (aux[i] && !ft_strncmp(aux[i], "-", 1))
		i++;
	if (aux[i])
		return (aux[i]);
	return (NULL);
}

int	check_command(t_process *prcs, char ***exec_args, char **envp)
{
	char 	**aux;
	// int		fd;

	aux = ft_split(prcs->process, ' ');
	ft_free(aux, ft_word_count(prcs->process, ' '));
	/* fd = open(get_ifile(prcs->process), O_RDONLY);
	if (fd == -1)
	{
		perror("Error to open file");
		return (-1);
	} */
	if (prepare_command(prcs->process, exec_args, envp) == -1)
		return (-1);
	return (0);
}