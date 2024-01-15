#include "../Inc/minishell.h"

int	main(int argc, char **envp)
{
	t_shell	*new;
	char	*line;

	(void)envp;
	if (argc == 1)
	{
		new = (t_shell *)ft_calloc(1, sizeof(t_shell));
		while (42)
		{
			line = readline("minishall$ ");
			if (line[0] != 0)
			{
				if (!ft_strncmp(line, "exit", 4))
					exit(EXIT_SUCCESS);
				if (input_parser(line, new) == -1)
					exit(EXIT_FAILURE);
				add_history(line);
				// executor(new);
			}
			
			printf("%s\n", line);
		}
	}
	else
		printf("Too much arguments\n");
	return (0);
}
