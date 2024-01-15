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

		}
	}
	else
	{
		if (check_builtins(all->lst_process))
			return ;
		if (check_command(all->lst_process, &all->exec_args, envp))
			return ;
	}
}