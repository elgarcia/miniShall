#include "../Inc/minishell.h"

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

void	check_red(char *in, char *in2, t_process **aux, int *i)
{
	if (!ft_strncmp(in, "|", 1))
	{
		(*aux)->type = PIPE;
		(*aux)->next = (t_process *)ft_calloc(1, sizeof(t_process));
		*aux = (*aux)->next;
		(*aux)->process = NULL;
		(*aux)->type = -1;
		*i += 1;
	}
	else if (!ft_strncmp(in, ">", 1) && (in2 && !ft_strncmp(in2, ">", 1)))
	{
		(*aux)->type = APND;
		*i += 2;
		//append
	}
	else if (!ft_strncmp(in, "<", 1) && (in2 && !ft_strncmp(in2, "<", 1)))
	{
		(*aux)->type = HD;
		*i += 2;
		//heredoc
	}
	else
		check_redaux(in, *aux, i);
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
	while (new->input[i])
	{
		if (i == 0)
		{
			aux = (t_process *)ft_calloc(1, sizeof(t_process));
			aux->process = NULL;
			aux->type = -1;
		}
		if (new->lst_process == NULL)
			new->lst_process = aux;
		check_red(new->input[i], new->input[i + 1], &aux, &i);
		if (new->input[i])
		{
			if (aux->process != NULL)
				aux->process = ft_strjoinup(&aux->process, " ");
			else
				new->n_process += 1;
			aux->process = ft_strjoinup(&aux->process, new->input[i]);
		}
		i++;
	}
	return (ft_free(new->input, ft_word_count(line, ' ')), 0);
}
