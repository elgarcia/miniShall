#include "../Inc/minishell.h"

void	exec_process(t_shell *all, char **envp)
{
	t_process *aux;

	all->exec_args = NULL;
	aux = all->lst_process;
	if (all->n_process > 1)
	{
		while (aux)
		{
			aux = aux->next;
		}
	}
	else
	{
		if (check_builtins(&all->lst_process, all))
			return ;
		if (check_command(all, &all->lst_process, &all->exec_args, envp))
		{
			pid_t test = fork();

			if (test == 0)
				execve(all->exec_args[0], all->exec_args, all->paths->envp);
			else
				wait(NULL);
			return ;
		}
	}
}
