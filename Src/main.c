#include "../Inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	(void)envp;
	if (argc == 1)
	{
		while (42)
		{
			line = readline("minishall$ ");
			if (line[0] != 0)
				add_history(line);
			if (!ft_strncmp(line, "exit", 4))
				exit(EXIT_SUCCESS);
			printf("%s\n", line);
		}
	}
	else
		printf("Too much arguments\n");
	return (0);
}