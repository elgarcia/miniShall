#include "../Inc/minishell.h"

extern int g_pid;

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
			init_pipex(&all->pipes[i], &all->sons[i]);
			if (!check_command(all, &aux, &all->exec_args, i))
			{
				//checkear pipes para abrir pipes
				if (all->sons[i] == 0)
					execve(all->exec_args[0], all->exec_args, all->paths->envp);
			}
			aux = aux->next;
			i++;
		}
		while (j < i)
			waitpid(all->sons[j], NULL, 0);
	}
	else
	{
		if (check_builtins(&all->lst_process, all, line))
			return ;
		init_pipex(&all->pipes[i], NULL);
		if (!check_command(all, &all->lst_process, &all->exec_args, i))
		{
			set_signals(1);
			pid_t test = fork();
			if (test == 0)
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			else
				waitpid(test, NULL, 0);
		}
	}
}
