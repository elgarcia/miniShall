#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structures.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

#define RED_TEXT    "\033[1;31m"
#define GREEN_TEXT  "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT  "\033[0m"
#define BLUE_TEXT	"\e[0;34m"

/* parser.c */
int			input_parser(char *line, t_shell *new, char **envp);
int			check_process(t_shell *new, char **envp);

/* utils.c*/
void		ft_free(char **arg, int size);
int			ft_word_count(const char *s1, char delimiter);
int			ft_strcmp(char *s1, char *s2);

// ENVP LIST
void		fill_init_env_list(t_paths *paths, char **envp);
t_env_lst	*find_env_node(t_env_lst *env_lst, char *key);
t_env_lst	*add_env_node(t_env_lst *head, char *name, char *value, int equal);
t_env_lst	*duplicate_lst(const t_env_lst *head);
t_env_lst	*duplicate_env_node(const t_env_lst *node);
void		ft_lstdelone_env(t_env_lst *lst);
void		ft_lstclear_env(t_env_lst **lst);
void		delete_env_value(t_env_lst *lst, char *key);
void		print_env_list(t_env_lst *head);

// SORT ENV_LST
t_env_lst	*insert_sorted(t_env_lst *head, char *name, \
						char *value, int equal);
void		sort_env_list(t_env_lst **head);
// CD UTILS
char		*resolve_parent_references(char *current_dir, char *target);
char		*resolve_single_component(char *current_path, char *component);
void		update_pwd_variables(t_paths *paths, char *new_pwd);
int			arg_counter(char **argv);
char		*get_previous_dir(char *str);
char		*join_paths(const char *path1, const char *path2);

// EXPORT UTILS

void		add_export_node(t_paths *paths, char *name, char *value, int equal);
void		add_env_variable(t_paths *paths, char *name, char *value,
				int equal);
int			extract_name_value(char *arg, char **name, char **value);

// BUILTINS
void		ft_env(t_paths *paths);
void		ft_cd(t_paths *paths, char **dir);
int			ft_pwd(t_paths *paths);
int			ft_echo(char **argv);
void		ft_export(t_paths *paths, char **argv, int i);
void		ft_exit(t_shell *shell);
void		ft_unset(t_paths *paths, char **argv);

// SIGNAL
void		handle_signal(int signo);
#endif
