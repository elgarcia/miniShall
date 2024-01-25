#include "../Inc/minishell.h"

extern int g_pid;

void	close_pipes(t_shell *all)
{
	dup2(all->og_infile, STDIN_FILENO);
	dup2(all->og_outfile, STDOUT_FILENO);
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
	if (all->n_process > 1)
	{
		while (aux)
		{
			if (check_builtins(&aux, all, line))
				return ;
			init_pipex(all, aux, &all->sons[i]);
			if (!check_command(all, &aux, &all->exec_args))
			{
				if (all->sons[i] == 0)
				{
					close(all->pipes[0]);
					if (aux->n_process != all->n_process - 1)
						dup2(all->pipes[1], STDOUT_FILENO);
					else
						dup2(STDOUT_FILENO, all->pipes[1]);
					execve(all->exec_args[0], all->exec_args, all->paths->envp);
				}
				else
				{
					close(all->pipes[1]);
					dup2(all->pipes[0], STDIN_FILENO);
				}
			}
			aux = aux->next;
			i++;
		}
		while (j != i)
			waitpid(all->sons[j++], NULL, 0);
		close_pipes(all);
	}
	else
	{
		if (check_builtins(&all->lst_process, all, line))
			return ;
		init_pipex(all, aux, &all->sons[i]);
		if (!check_command(all, &all->lst_process, &all->exec_args))
		{
			g_pid = all->sons[i];
			if (all->sons[i] == 0)
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			else
				waitpid(all->sons[i], NULL, 0);
		}
		close_pipes(all);
		g_pid = 0;
	}
}
