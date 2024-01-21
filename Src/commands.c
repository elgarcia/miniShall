#include "../Inc/minishell.h"

static int	reassign_path(char ***aux2, t_env_lst *envp)
{
	char	*aux;

	aux = ft_strdup(envp->value);
	*aux2 = ft_split(aux, ':');
	if (!*aux2)
		return (-1);
	free(aux);
	return (0);
}

int	assign_path(char ***exec_args, char *command, t_env_lst *envp)
{
	char	*aux_path;
	t_env_lst *aux;
	char	**aux2;
	int		flag;

	aux = envp;
	while (aux)
	{
		if (!ft_strncmp(aux->name, "PATH", 4))
		{
			if (reassign_path(&aux2, aux) == -1)
				return (-1);
			flag = search_path(aux2, &aux_path, command, exec_args);
			return (ft_free(aux2, ft_word_count(aux->value, ':')), flag);
		}
		aux = aux->next;
	}
	return (-1);
}

int	check_cmd(char *command, char ***exec_args)
{
	if (command[0] == '/')
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			(*exec_args)[0] = ft_strdup(command);
			if (!(*exec_args)[0])
				return (ft_free(*exec_args, 1), -1);
			return (0);
		}
		else
			return (printf("%s: command not found\n", command), -1);
	}
	else if (!ft_strncmp(command + ft_strlen(command) - 3, ".sh", 3))
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			(*exec_args)[0] = ft_strdup(command);
			if (!(*exec_args)[0])
				return (ft_free(*exec_args, 1), -1);
			return (0);
		}
		else
			return (printf("%s: command not found\n", command), -1);
	}
	return (1);
}

static int	init_cmd(int *aux, char ***cmd_split, char *process)
{
	*cmd_split = ft_split(process, ' ');
	if (!*cmd_split)
		return (-1);
	*aux = ft_word_count(process, ' ') + 1;
	return (0);
}

int	prepare_command(char *process, char ***exec_args, t_env_lst *envp)
{
	int		aux;
	char	**cmd_split;
	int		path_rt;

	if (init_cmd(&aux, &cmd_split, process) == -1)
		return (-1);
	*exec_args = (char **)ft_calloc(aux, sizeof(char *));
	if (!*exec_args)
		return (ft_free(cmd_split, aux), -1);
	aux = check_cmd(cmd_split[0], exec_args);
	if (aux == 1)
	{
		path_rt = assign_path(exec_args, cmd_split[0], envp);
		if (path_rt == -1 || path_rt == -2)
		{
			ft_free(cmd_split, ft_word_count(process, ' '));
			return (free(*exec_args), -1);
		}
	}
	if (aux == -1 || init_execargs(exec_args, process) == -1)
		return (ft_free(cmd_split, ft_word_count(process, ' ')), -1);
	return (ft_free(cmd_split, ft_word_count(process, ' ')), 0);
}
