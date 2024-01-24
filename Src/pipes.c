#include "../Inc/minishell.h"

void	init_pipex(pid_t *pid)
{
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

int	open_file(char *file, int *fd)
{
	char *aux;
	
	aux = get_ifile(file);
	if (!aux)
		return (0);
	*fd = open(aux, O_RDONLY);
	if (*fd == -1)
	{
		perror("Failed to open output file");
		free(aux);
		return (-1);//error 1(?)
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		perror("New file dup2 error");
		close(*fd);
		return (-1);
	}
	free(aux);
	close(*fd);
	return (0);
}
//acortar
int	treat_fork(t_process *argv, char ***exec_args, t_shell *all)
{
	int	input_fd;
	int	open_rt;

	input_fd = -1;
	if (prepare_command(argv->process, exec_args, all->paths->env_lst) == -1)
		return (-1); //exit(127);
	if (argv->n_process == 0)
	{
		open_rt = open_file(argv->process, &input_fd);
		if (open_rt == -1)
			return (-1);
	}
	else
		dup2(all->pipes[0], STDIN_FILENO);
	if (argv->n_process == all->n_process - 1)
		dup2(STDOUT_FILENO, all->pipes[1]);
	else
		dup2(all->pipes[1], STDOUT_FILENO);
	return (0);
}

int	treat_single(char *argv, char ***exec_args, t_env_lst *envp)
{
	int	input_fd;
	int	ret_value;

	input_fd = -1;
	if (prepare_command(argv, exec_args, envp) == -1)
		return (-1); //exit(127);
	ret_value = open_file(argv, &input_fd);
	if (ret_value == -1)
		return (-1);
	return (0);
}
