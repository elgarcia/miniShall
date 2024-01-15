#include "../Inc/minishell.h"

int	check_process(t_shell *new)
{
	t_process	*aux;
	char		**sp_aux;

	aux = new->lst_process;
	while (aux)
	{
		if (aux->type == PIPE || aux->type == -1)
		{
			sp_aux = ft_split(aux->process, ' ');
			if (access(sp_aux[0], F_OK | X_OK) != 0)
				return (ft_free(sp_aux, ft_word_count(aux->process, ' ')), -1);
			ft_free(sp_aux, ft_word_count(aux->process, ' '));
		}
		aux = aux->next;
	}
	return (0);
}
void	check_redaux(char *in, t_process *aux, int *i)
{
	(void)aux;
	if (!ft_strncmp(in, "<", 1))
	{
		aux->type = IRD;
		*i += 1;
		//input redirect
	}
	else if (!ft_strncmp(in, ">", 1))
	{
		aux->type = ORD;
		*i += 1;
		//output redirecct
	}
}

void	check_red(char *in, char *in2, t_process *aux, int *i)
{
	if (!ft_strncmp(in, "|", 1))
	{
		aux->type = PIPE;
		aux = aux->next;
		aux = (t_process *)ft_calloc(1, sizeof(t_process));
		aux->process = NULL;
		aux->type = -1;
	}
	else if (!ft_strncmp(in, ">", 1) && (in2 && !ft_strncmp(in2, ">", 1)))
	{
		aux->type = APND;
		*i += 2;
		//append
	}
	else if (!ft_strncmp(in, "<", 1) && (in2 && !ft_strncmp(in2, "<", 1)))
	{
		aux->type = HD;
		*i += 2;
		//heredoc
	}
	else
		check_redaux(in, aux, i);
}

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
		if (i == 0)
		{
			aux = (t_process *)ft_calloc(1, sizeof(t_process));
			aux->process = NULL;
			aux->type = -1;
		}
		check_red(new->input[i], new->input[i + 1], aux, &i);
		if (new->input[i])
			aux->process = ft_strjoinup(&aux->process, new->input[i]);
		i++;
	}
	return (check_process(new));
}
