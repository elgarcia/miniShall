#include "../Inc/minishell.h"

extern int g_pid;

void	close_pipes(t_shell *all)
{
	close(all->pipes[0]);
	close(all->pipes[1]);
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
		if (check_builtins(all, line))
			return (free_prcs(all));
		init_pipex(all, aux, &all->sons[i]);
		set_signals(1);
		if (all->sons[i] == 0)
		{
			//Check process type (|, <, >, <<, >>)
			if (!check_command(all, &aux, &all->exec_args))
			{
				close(all->pipes[0]);
				if (all->n_process > 1)
					dup2(all->pipes[1], STDOUT_FILENO);
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			}
			else
				exit(EXIT_FAILURE);
		}
		else
		{
			close(all->pipes[1]);
			if (all->n_process > 1)
				dup2(all->pipes[0], STDIN_FILENO);
		}
		close_pipes(all);
		aux = aux->next;
		i++;
	}
	while (j != i)
			waitpid(all->sons[j++], NULL, 0);
	dup2(all->og_infile, STDIN_FILENO);
	dup2(all->og_outfile, STDOUT_FILENO);
	free_prcs(all);
}
