#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "structures.h"

/* parser.c */
int		input_parser(char *line, t_shell *new, char **envp);
int		check_process(t_shell *new, char **envp);

/* utils.c*/
void	ft_free(char **arg, int size);
int		ft_word_count(const char *s1, char delimiter);

// ENVP LIST
void					fill_init_env_list(t_paths *paths, char **envp);
t_env_lst				*find_env_node(t_env_lst *env_lst, char *key);
t_env_lst				*add_env_node(t_env_lst *head, \
						char *name, char *value, int equal);
void					ft_lstdelone_env(t_env_lst *lst);
void					ft_lstclear_env(t_env_lst **lst);
void					delete_env_value(t_env_lst *lst, char *key);
void					print_env_list(t_env_lst *head);

// BUILTINS
void					ft_env(t_paths *paths);
void					ft_cd(t_paths *paths, char *dir);
int						ft_pwd(void);
int						ft_echo(char **argv, int argc);
void					ft_export(t_paths *paths, char **argv, int i);
#endif
