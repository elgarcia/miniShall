#include "../Inc/minishell.h"

void	init_minishell(t_shell **all)
{
    (*all) = (t_shell *)ft_calloc(1, sizeof(t_shell));
	(*all)->n_process = 0;
	(*all)->input = NULL;
	(*all)->paths = malloc(sizeof(t_paths));
	(*all)->paths->pwd = ft_strdup(getenv("PWD"));
	(*all)->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
	(*all)->paths->home = ft_strdup(getenv("HOME"));
	(*all)->og_infile = dup(STDIN_FILENO);
	(*all)->og_outfile = dup(STDOUT_FILENO);
}

void	init_pikes(t_shell **all)
{
	(*all)->sons = (pid_t *)ft_calloc((*all)->n_process, sizeof(pid_t));
	(*all)->pipes = (int **)ft_calloc((*all)->n_process, sizeof(int *));
}

void	free_pipes(t_shell *all, int ***pipes, int n_pipes)
{
	int	i;

	i = 0;
	if (dup2(all->og_infile, STDIN_FILENO) == -1)
	{
		perror("New file dup2 error");
		exit(EXIT_FAILURE);
	}
	while (i < n_pipes)
		free((*pipes)[i++]);
	free(*pipes);
}

void	free_pikes(t_shell **all)
{
	free((*all)->sons);
	free_pipes(*all, &(*all)->pipes, (*all)->n_process);
}