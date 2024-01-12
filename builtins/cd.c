/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:59:47 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/11 17:08:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

# define PATH_MAX 1024

t_env_lst *find_env_node(t_env_lst *env_lst, char *key)
{
    int key_len = ft_strlen(key);
    t_env_lst *tmp = env_lst;

    while (tmp != NULL && ft_strncmp(tmp->name, key, key_len) != 0)
    {
        tmp = tmp->next;
    }
    return tmp;
}

void update_pwd_variables(t_paths *paths, char *new_pwd)
{
    t_env_lst *pwd_node;
	t_env_lst *old_pwd_node;

	pwd_node = find_env_node(paths->env_lst, "PWD");
    if (pwd_node)
    {
        free(pwd_node->value);
        pwd_node->value = ft_strdup(new_pwd);
    }
    old_pwd_node = find_env_node(paths->env_lst, "OLDPWD");
    if (old_pwd_node)
    {
        free(old_pwd_node->value);
        old_pwd_node->value = ft_strdup(paths->pwd);
    }
    free(paths->old_pwd);
    paths->old_pwd = ft_strdup(paths->pwd);
    free(paths->pwd);
    paths->pwd = ft_strdup(new_pwd);
}

char *join_paths(const char *path1, const char *path2)
{
    char *result = ft_strjoin(path1, "/");
    char *tmp = ft_strjoin(result, path2);
    free(result);
    return tmp;
}

void cd_command(t_paths *paths, char *dir)
{
    char *new_dir;
	char *current_dir;

    if (dir == NULL || ft_strncmp(dir, "~", 1) == 0)
        new_dir = ft_strdup(paths->home);
    else if (dir[0] == '/')
        new_dir = ft_strdup(dir);
    else
    {
        current_dir = getcwd(NULL, 0);
        new_dir = join_paths(current_dir, dir);
        free(current_dir);
    }
    if (chdir(new_dir) != 0)
        perror("cd");
    else
        update_pwd_variables(paths, new_dir);
    free(new_dir);
}

void	clear_all_env(t_paths *paths)
{
	ft_lstclear_env(&paths->env_lst);
	if (paths->pwd)
		free(paths->pwd);
	if (paths->old_pwd)
		free(paths->old_pwd);
}

int main(int argc, char **argv, char **envp)
{
    t_paths paths;

	paths.pwd = ft_strdup(getenv("PWD"));
	paths.old_pwd = ft_strdup(getenv("OLDPWD"));
	paths.home = getenv("HOME");
    fill_init_env_list(&paths, envp);
    printf("Lista de entornos:\n");
    //print_env_list(paths.env_lst);
	cd_command(&paths, argv[1]);
	printf("\n\n\n\n\n");
    printf("Lista de entornos luego de cambiar:\n");
    print_env_list(paths.env_lst);
	clear_all_env(&paths);
    return 0;
}
