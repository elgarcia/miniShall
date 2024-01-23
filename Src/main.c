#include "../Inc/minishell.h"
#include <errno.h>

void	change_shell(t_shell *shell)
{
	char	*tmp;
	tmp = ft_strjoin(shell->paths->pwd, "/minishall");
	add_export_node(shell->paths, "SHELL", tmp, 1);
	free(tmp);
}
/*
static int	init_struct(t_shell *new, char **envp)
{
	struct sigaction	sa;

	new->paths = malloc(sizeof(t_paths));
	if (!new->paths)
		return (-1);
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	new->paths->pwd = ft_strdup(getenv("PWD"));
	new->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
	new->paths->home = ft_strdup(getenv("HOME"));
	fill_init_env_list(new->paths, envp);
	new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
	change_shell(new);
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT, &sa, NULL) ==
		-1)
		ft_exit(new);
	return (0);
}
*/
int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;
	char	*line;

	(void)argv;
	if (argc == 1)
	{
		init_minishell(&new);
		fill_init_env_list(new->paths, envp);
		new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
		change_shell(new);
		while (42)
		{
			set_signals(0);
			line = readline(GREEN_TEXT "minishall$ "RESET_TEXT);
			if (line == NULL) {
				printf("Exit\n");
				ft_exit(new);
			}
			if (line[0] != 0)
			{
				if (!ft_strncmp(line, "exit", 5))
					ft_exit(new);
				if (input_parser(line, new) == -1)
					exit(EXIT_FAILURE);
				add_history(line);
				init_pikes(&new);
				exec_process(new, line);
				free(line);
				free_pikes(&new);
			}
			// free_null(&line);
		}
	}
	else
		printf("Too many arguments\n");
	return (0);
}
