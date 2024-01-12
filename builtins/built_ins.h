/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/12 14:59:04 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct s_paths
{
	char				*home;
	char				*pwd;
	char				*old_pwd;
	char				**envp;
	t_env_lst			*env_lst;
}						t_paths;

// ENVP LIST
void					fill_init_env_list(t_paths *paths, char **envp);
t_env_lst				*add_env_node(t_env_lst *head, \
						char *name, char *value);
void					ft_lstdelone_env(t_env_lst *lst);
void					ft_lstclear_env(t_env_lst **lst);
void					print_env_list(t_env_lst *head); // delete later
#endif
