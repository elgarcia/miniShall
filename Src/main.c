#include "../Inc/minishell.h"

#define RED_TEXT    "\033[1;31m"
#define GREEN_TEXT  "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT  "\033[0m"

void	free_split(char **argv)
{
	int		i;
	
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

int	execute(t_paths *paths, char *line, int argc)
{
	char	**argv;
	
	argv = ft_split(line, ' ');
	if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(paths, argv);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd(paths);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(paths);
	else if (ft_strncmp(line, "export", 6) == 0)
		ft_export(paths, argv, 0);
	else if(ft_strncmp(line, "echo", 4) == 0)
		ft_echo(argv, argc);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ft_unset(paths, line);
	if (argv)
		free_split(argv);
}

static int	init_struct(t_shell *new, char **envp)
{
	new->paths = malloc(sizeof(t_paths));
	if (!new->paths)
		return (-1);
	new->paths->pwd = ft_strdup(getenv("PWD"));
	new->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
	new->paths->home = ft_strdup(getenv("HOME"));
	fill_init_env_list(new->paths, envp);
	new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;
	char	*line;

	if (argc == 1)
	{
		new = (t_shell *)ft_calloc(1, sizeof(t_shell));
		if (!new || init_struct(new, envp) == -1)
			exit(EXIT_FAILURE);
		while (42)
		{
			line = readline(GREEN_TEXT"minishall$ "RESET_TEXT);
			if (line[0] != 0)
			{
				// if (input_parser(line, new, envp) == -1)
				//	exit(EXIT_FAILURE);
				// add_history(line);
				execute(new->paths, line, argc);
			}
			if (!ft_strncmp(line, "exit", 4))
				ft_exit(new);
			//printf("%s\n", line);
			printf("\n");
		}
	}
	else
		printf("Too many arguments\n");
	return (0);
}
