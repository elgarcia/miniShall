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