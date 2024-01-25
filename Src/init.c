#include "../Inc/minishell.h"

void	init_minishell(t_shell **all)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
    (*all) = (t_shell *)ft_calloc(1, sizeof(t_shell));
	(*all)->n_process = 0;
	(*all)->input = NULL;
	(*all)->paths = malloc(sizeof(t_paths));
	(*all)->paths->pwd = ft_strdup(getenv("PWD"));
	(*all)->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
	(*all)->paths->home = ft_strdup(getenv("HOME"));
	(*all)->paths->last_exit_status = 0;
	(*all)->og_infile = dup(STDIN_FILENO);
	(*all)->og_outfile = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_exit(*all);
}

void	init_pikes(t_shell **all)
{
	(*all)->sons = (pid_t *)ft_calloc((*all)->n_process, sizeof(pid_t));
	(*all)->pipes = (int *)ft_calloc(2, sizeof(int));
	(*all)->fd_in = -1;
	(*all)->fd_out = -1;
}

void	free_pikes(t_shell **all)
{
	free((*all)->sons);
	free((*all)->pipes);
}
