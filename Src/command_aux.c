#include "../Inc/minishell.h"

int	init_execargs(char ***ex_argc, char *command)
{
	char	**aux;
	int		i;

	i = 0;
	aux = ft_split(command, ' ');
	if (!aux)
		return (-1);
	while (++i < ft_word_count(command, ' '))
	{
		(*ex_argc)[i] = ft_strdup(aux[i]);
		if (!(*ex_argc)[i])
			return (ft_free(*ex_argc, i), \
			ft_free(aux, ft_word_count(command, ' ')), -1);
	}
	return (ft_free(aux, ft_word_count(command, ' ')), 0);
}

int	search_path(char **env_1, char	**actual_path, \
	char *command, char ***exec_args)
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
				return (ft_free(*exec_args, 1), free(*actual_path), -1);
			return (free(*actual_path), free(aux), 0);
		}
		else
			double_free(&aux, actual_path);
	}
	return (printf("%s: command not found\n", command), -2);
}

void	double_free(char **aux, char **actual_path)
{
	free(*actual_path);
	free(*aux);
}