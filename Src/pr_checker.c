#include "../Inc/minishell.h"

static int check_builtins_aux(t_process *prcs, char **aux)
{
	if (!ft_strncmp(aux[0], "export", 6))
	{
		//ft_export
		return (ft_free(aux, ft_word_count(prcs->process, ' ')), 1);
	}
	if (!ft_strncmp(aux[0], "unset", 5))
	{
		//ft_unset
		return (ft_free(aux, ft_word_count(prcs->process, ' ')), 1);
	}
	if (!ft_strncmp(aux[0], "env", 3))
	{
		//ft_env
		return (ft_free(aux, ft_word_count(prcs->process, ' ')), 1);
	}
	return (ft_free(aux, ft_word_count(prcs->process, ' ')), 0);
}

int	check_builtins(t_process *prcs)
{
	char **aux;

	aux = ft_split(prcs->process, ' ');
	if (!ft_strncmp(aux[0], "echo", 4))
	{
		//ft_echo
		return (ft_free(aux, ft_word_count(prcs->process, ' ')), 1);
	}
	else if (!ft_strncmp(aux[0], "cd", 2))
	{
		//ft_cd
		return (ft_free(aux, ft_word_count(prcs->process, ' ')), 1);
	}
	else if (!ft_strncmp(aux[0], "pwd", 3))
	{
		//ft_pwd
		return (ft_free(aux, ft_word_count(prcs->process, ' ')), 1);
	}
	else
		return (check_builtins_aux(prcs, aux));
	return (ft_free(aux, ft_word_count(prcs->process, ' ')), 0);
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