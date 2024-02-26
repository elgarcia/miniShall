/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:12:58 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/26 01:13:00 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void replace_envp(char *name, char *value, char **envp)
{
    int i;
    int len;
    i = 0;
    len = ft_strlen(name);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0)
        {
            ft_memmove(envp[i] + len, value, ft_strlen(value));
            return ;
        }
        i++;
    }
}

void    add_envp(char *name, char *value, t_paths *paths, int flag)
{
    int i;
    int len;
    char **new_envp;
    i = 0;
    len = 0;
    while (paths->envp[len])
        len++;
    new_envp = malloc(sizeof(char *) * (len + 2));
    while (i < len)
    {
        new_envp[i] = ft_strdup(paths->envp[i]);
        i++;
    }
    new_envp[i] = ft_strjoin(name, value);
    new_envp[i + 1] = NULL;
    if (flag == 1)
        ft_free(paths->envp, arg_counter(paths->envp) + 1);
    paths->envp = new_envp;
}

void    create_envp(t_paths *paths, char **envp)
{
    int i;
    i = 0;
    while (envp[i])
        i++;
    paths->envp = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i])
    {
        paths->envp[i] = ft_strdup(envp[i]);
        i++;
    }
    paths->envp[i] = NULL;
}
