#include "../Inc/minishell.h"

int	main(int argc, char **envp)
{
	t_shell	*new;
	char	*line;

	if (argc == 1)
	{
		new = (t_shell *)ft_calloc(1, sizeof(t_shell));
		while (42)
		{
			line = readline("minishall$ ");
			if (line[0] != 0)
			{
				if (input_parser(line, new, envp) == -1)
					exit(EXIT_FAILURE);
				add_history(line);
			}
			if (!ft_strncmp(line, "exit", 4))
				exit(EXIT_SUCCESS);
			printf("%s\n", line);
		}
	}
	else
		printf("Too much arguments\n");
	return (0);
}
