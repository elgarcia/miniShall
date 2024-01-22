#include "../Inc/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	g_pid = 0;

void	free_split(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

int	execute(t_shell *shell, char *line)
{
	char	**argv;

	argv = ft_split(line, ' ');
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		ft_cd(shell->paths, argv);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		ft_pwd(shell->paths);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		ft_env(shell->paths);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		ft_export(shell->paths, argv, 1);
	else if (ft_strncmp(argv[0], "echo", 5) == 0)
		ft_echo(argv);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		ft_unset(shell->paths, argv);
	else if (!ft_strncmp(argv[0], "exit", 5))
	{
		free_split(argv);
		ft_exit(shell);
	}
	if (argv)
		free_split(argv);
	return (0);
}

void	change_shell(t_shell *shell)
{
	char	*tmp;
	tmp = ft_strjoin(shell->paths->pwd, "/minishall");
	add_export_node(shell->paths, "SHELL", tmp, 1);
	free(tmp);
}

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

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;
	char	*line;

	if (argc == 1 && argv[0])
	{
		new = (t_shell *)ft_calloc(1, sizeof(t_shell));
		if (!new || init_struct(new, envp) == -1)
			exit(EXIT_FAILURE);
		while (42)
		{
			line = readline(GREEN_TEXT "minishall$ > "RESET_TEXT);
			if (!line)
			{
				write(1, "exit\n", 5);
				ft_exit(new);
			}
			if (line[0] != 0)
			{
				// if (input_parser(line, new, envp) == -1)
				//	exit(EXIT_FAILURE);
				add_history(line);
				execute(new, line);
				free(line);
			}
		}
	}
	else
		printf("Too many arguments\n");
	return (0);
}
