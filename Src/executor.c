#include "../Inc/minishell.h"

void	exec_process(t_shell *all, char **envp)
{
	t_process	*aux;
	int			i;

	i = 0;
	all->exec_args = NULL;
	aux = all->lst_process;
	if (all->n_process > 1)
	{
		while (aux)
		{
			if (check_builtins(&aux, all))
				;
			else if (check_command(all, &aux, &all->exec_args, envp))
			{
				//checkear pipes para abrir pipes
				while (i < all->n_process)
				{
					init_pipex(&all->sons[i], &all->sons[i]);
					if (all->sons[i] == 0)
						execve(all->exec_args[0], all->exec_args, all->paths->envp);
					else
						wait(NULL);
				}
				while (wait(NULL) > 0)
					;
			}
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
