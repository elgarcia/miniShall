#include "../Inc/minishell.h"
int	input_parser(char *line, t_shell *new)
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
			if (aux == NULL)
				aux = (t_process *)ft_calloc(1, sizeof(t_process));
			else
			{
				aux = aux->next;
				i++;
			}
		}
		if (new->input[i])
			aux = ft_strjoin(aux, new->input[i]);
		i++;
	}
	return (0);
}
