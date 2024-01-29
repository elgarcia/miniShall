#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "structures.h"
# include <readline/history.h>
# include <readline/readline.h>
# include "get_next_line/get_next_line.h"

#define RED_TEXT    "\033[1;31m"
#define GREEN_TEXT  "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT  "\033[0m"
#define BLUE_TEXT	"\e[0;34m"

/* parser.c */
int			check_process(t_shell *new, char **envp);
int			input_parser(char *line, t_shell *new); //split del input
// int		check_process(t_shell *new); //comprueba que los procesos sean validos
void		check_redaux(char *in, t_process *aux, int *i); //red checks
void		check_red(char *in, char *in2, t_process **aux, int *i); //red checks

/* utils.c*/
void		ft_free(char **arg, int size);
int			ft_word_count(const char *s1, char delimiter);
int			ft_strcmp(char *s1, char *s2);
void		*free_null(char **s);
char		*ft_strjoinup(char **s1, char *s2);

/* executor.c */
void		exec_process(t_shell *all, char *line);

/* pr_checker.c */
int			check_builtins(t_process **prcs, t_shell *all, char *line);
int			check_command(t_shell *all, t_process **prcs, char ***exec_args, \
			int i);
void		free_prcs(t_process **pr, t_shell *all);
char		*get_ifile(char *process);

/* command_aux.c */
int			search_path(char **env_1, char	**actual_path, \
			char *command, char ***exec_args);
int			init_execargs(char ***ex_argc, char *command);

/* commands.c */
int			check_cmd(char *command, char ***exec_args);
int			prepare_command(char *process, char ***exec_args, t_env_lst *envp);
int			assign_path(char ***exec_args, char *command, t_env_lst *envp);
void		double_free(char **aux, char **actual_path);

/* pipes.c */
void		init_pipex(int **pipe_fd, pid_t *pid);
int			open_file(char *file, int *fd, int *pipe_fd);
int			treat_fork(int i, t_process *argv, char ***exec_args, t_shell *all);
int			treat_single(char *argv, char ***exec_args, t_env_lst *envp, int *pipe);

/* init.c */
void		init_minishell(t_shell **all);
void		init_pikes(t_shell **all);
void		free_pikes(t_shell **all);
void		free_pipes(t_shell *all, int ***pipes, int n_pipes);

// ENVP LIST
void		fill_init_env_list(t_paths *paths, char **envp);
t_env_lst	*find_env_node(t_env_lst *env_lst, char *key);
t_env_lst	*add_env_node(t_env_lst *head, char *name, char *value, int equal);
t_env_lst	*duplicate_lst(const t_env_lst *head);
t_env_lst	*duplicate_env_node(const t_env_lst *node);
t_env_lst	*add_env_node(t_env_lst *head, \
			char *name, char *value, int equal);
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
char		*get_full_path(char *current_dir, char *target);
char		*get_previous_dir(char *str);
char		*join_paths(const char *path1, const char *path2);

// EXPORT UTILS

void		add_export_node(t_paths *paths, char *name, char *value, int equal);
void		add_env_variable(t_paths *paths, char *name, char *value,
				int equal);
int			extract_name_value(char *arg, char **name, char **value);

// BUILTINS
void		ft_env(t_paths *paths, char **argv);
void		ft_cd(t_paths *paths, char **dir);
int			ft_pwd(t_paths *paths);
int			ft_echo(t_paths *paths, char **argv);
void		ft_export(t_paths *paths, char **argv, int i);
void		ft_exit(t_shell *shell);
void		ft_unset(t_paths *paths, char **argv);

// BUILTINS UTILS
int			arg_counter(char **argv);
char		**echo_split(char const *s, char c);
void		handle_variable(char **token, t_paths *paths);
void		handle_exit_status(char **token);
int			remove_char(char *str, char c);
int			quotes_counter(char *str);

// HISTORY
void	add_to_history(t_shell *shell, const char *line);
void	print_history(t_shell *shell);

// SIGNAL
void		handle_signal(int signo);
void		set_signals(int mode);
#endif
