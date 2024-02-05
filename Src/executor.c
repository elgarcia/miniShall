#include "../Inc/minishell.h"

extern int g_pid;

void	close_pipes(t_shell *all)
{
	dup2(all->og_infile, STDIN_FILENO);
	dup2(all->og_outfile, STDOUT_FILENO);
	all->fd_in = -1;
	all->fd_out = -1;
}

void	exec_type(t_shell *all, t_process *aux)
{
	char	**split;

	split = ft_split(aux->process, ' ');
	close(all->pipes[0]);
	if (aux->type == ORD)
	{
		all->fd_out = open(get_ifile(aux->process, arg_counter(split) - 1), O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, 0666);
		if (all->fd_out == -1)
			exit(EXIT_FAILURE);
		dup2(all->fd_out, STDOUT_FILENO);
		close(all->fd_out);
	}
	else
	{
		// if (all->n_process > 1)
			dup2(all->pipes[1], STDOUT_FILENO);
	}
}

void	exec_process(t_shell *all, char *line)
{
	t_process	*aux;
	int			i;
	int			j;

	i = 0;
	j = 0;
	all->exec_args = NULL;
	aux = all->lst_process;
	while (aux)
	{
		init_pipex(all, aux, &all->sons[i]);
		set_signals(1);
		if (all->sons[i] == 0)
		{
			//Check process type (|, <, >, <<, >>)
			exec_type(all, aux);
			if (check_builtins(all, line))
				exit(EXIT_SUCCESS);
			else if (!check_command(all, &aux, &all->exec_args, aux->type))
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			else
				exit(EXIT_FAILURE);
		}
		else
		{
			close(all->pipes[1]);
			if (all->n_process > 1)
				dup2(all->pipes[0], STDIN_FILENO);
		}
		aux = aux->next;
		i++;
	}
	while (j != i)
			waitpid(all->sons[j++], NULL, 0);
	close_pipes(all);
	free_prcs(all);
}
