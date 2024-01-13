#include "../Inc/minishell.h"

int	check_process(t_shell *new, char **envp)
{
	t_process	*aux;
	char		**sp_aux;

	aux = new->lst_process;
	while (aux)
	{
		sp_aux = ft_split(aux->process, ' ');
		if (access(sp_aux[0], F_OK | X_OK) != 0)
			return (ft_free(sp_aux, ft_word_count(sp_aux, ' ')), -1);
		ft_free(sp_aux, ft_word_count(sp_aux, ' '));
		aux = aux->next;
	}
	return (0);
}

int	input_parser(char *line, t_shell *new, char **envp)
{
	int			i;
	t_process	*aux;

	aux = new->lst_process;
	i = 0;
	new->input = ft_split(line, ' ');
	if (!new->input)
		return (-1);
	while (!new->input[i])
	{
		if (i == 0 || !ft_strncmp(new->input[i], "|", 1))
		{
			if (i != 0)
				aux = aux->next;
			aux = (t_process *)ft_calloc(1, sizeof(t_process));
			i++;
		}
		if (new->input[i])
			aux = ft_strjoin(aux, new->input[i]);
		i++;
	}
	return (check_process(new, envp));
}
