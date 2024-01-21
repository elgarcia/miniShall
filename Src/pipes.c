#include "../Inc/minishell.h"

void	init_pipex(int **pipe_fd, pid_t *pid)
{
    *pipe_fd = (int *)ft_calloc(2, sizeof(int));
	if (pipe(*pipe_fd) == -1)
	{
		perror("Pipe creation failed!");
		exit(EXIT_FAILURE);
	}
	if (pid)
	{
		*pid = fork();
		if (*pid < 0)
		{
			perror("Fork failed!");
			exit(EXIT_FAILURE);
		}
	}
}
void	open_file(char *file, int *fd, int *pipe_fd)
{
	char *aux;
	
	aux = get_ifile(file);
	if (!aux)
		return ;
	*fd = open(aux, O_RDONLY);
	if (*fd == -1)
	{
		perror("Failed to open output file");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(aux);
		//error 1(?)
	}
	free(aux);
}


void	treat_fork(int *pipes, char *argv, char ***exec_args, t_env_lst *envp)
{
	int	input_fd;

	open_file(argv, &input_fd, pipes);
	close(pipes[0]);
	if (prepare_command(argv, exec_args, envp) == -1)
	{
		close(pipes[1]);
		return ; //exit(127);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("New file dup2 error");
		close(pipes[1]);
		close(input_fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipes[1], STDOUT_FILENO) == -1)
	{
		close(pipes[1]);
		perror("Child dup2 error");
		exit(EXIT_FAILURE);
	}
	close(pipes[1]);
	close(input_fd);
}

int	treat_single(char *argv, char ***exec_args, t_env_lst *envp, int *pipe)
{
	int	input_fd;

	input_fd = -1;
	open_file(argv, &input_fd, pipe);
	if (prepare_command(argv, exec_args, envp) == -1)
	{
		close(input_fd);
		return (-1); //exit(127);
	}
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("New file dup2 error");
			close(pipe[1]);
			close(input_fd);
			exit(EXIT_FAILURE);
		}
	}
	close(pipe[0]);
	close(input_fd);
	return (0);
}
