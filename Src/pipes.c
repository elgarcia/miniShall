#include "../Inc/minishell.h"

void	init_pipex(int *pipe_fd, pid_t *pid)
{
    pipe_fd = (int *)ft_calloc(2, sizeof(int));
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed!");
		exit(EXIT_FAILURE);
	}
	*pid = fork();
	if (*pid < 0)
	{
		perror("Fork failed!");
		exit(EXIT_FAILURE);
	}
}
void	open_file(t_shell *all, int *fd, int *pipe_fd)
{
	*fd = open(argv[file], O_RDONLY);
	if (*fd == -1)
	{
		perror("Failed to open output file");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
}
