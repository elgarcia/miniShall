/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:53:39 by eliagarc          #+#    #+#             */
/*   Updated: 2024/03/06 12:38:42 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "structures.h"
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../get_next_line/get_next_line.h"
# include <errno.h>
# include <limits.h>

# define RED_TEXT "\033[1;31m"
# define GREEN_TEXT "\033[1;32m"
# define YELLOW_TEXT "\033[1;33m"
# define RESET_TEXT "\033[0m"
# define BLUE_TEXT "\e[0;34m"

/* parser.c */
int			input_parser(char *line, t_shell *new, int i);
void		check_redaux(char **in, t_process **aux, int *i, t_redir **red_aux);
void		check_red(char **in, t_process **aux, int *i, t_redir **red_aux);
void		new_proc(t_process **aux, t_shell *all, int n_proc,
				t_redir **red_aux);
void		parse_arg(t_process *aux, t_shell *new, int *i);

/* parser_aux.c */
void		assign_redir(t_process **aux, int *i, t_redir **red_aux,
				int rd_type);
int			is_ao(char *str);
int			check_cats(t_shell *all, t_process *aux);
void		check_exp(char **in, int *i, int j);

/* utils.c*/
void		ft_free(char **arg, int size);
int			ft_word_count(const char *s1, char delimiter);
int			ft_strcmp(char *s1, char *s2);
void		*free_null(char **s);
char		*ft_strjoinup(char **s1, char *s2);

/* utils_2.c */
int			ft_strlenchr(const char *s, char c);
char		**list_to_array(t_env_lst *env);
void	check_status(t_shell *all, int status);

/* envp.c */
void		replace_envp(char *name, char *value, char **envp);

/* executor.c */
void		exec_process(t_shell *all, int i, int j, int status);
void		close_pipes(t_shell *all);
void		exec_type(t_shell *all, t_process *aux, int split);
void		here_doc(t_shell *all, t_process *aux, int rd);
void		exec_son(t_shell *all, t_process *aux);

/* executor_aux.c */
void		reset_prc(t_shell *all);
void		pipe_man(t_shell *all);
void		init_executor(t_shell *all, t_process **aux, int *i, int *j);

/* pr_checker.c */
int			check_builtins(t_shell *all, t_process *aux);
int			check_command(t_shell *all, t_process **prcs, char ***exec_args);
void		free_prcs(t_shell *all);
char		*get_ifile(char *process, int inout);

/* command_aux.c */
int			search_path(char **env_1, char **actual_path, char *command,
				char ***exec_args);
int			init_execargs(char ***ex_argc, char *command);

/* commands.c */
int			check_cmd(char *command, char ***exec_args);
int			prepare_command(char *process, char ***exec_args, t_env_lst *envp);
int			assign_path(char ***exec_args, char *command, t_env_lst *envp);
void		double_free(char **aux, char **actual_path);

/* pipes.c */
void		init_pipex(t_shell *all, t_process *prc, pid_t *pid);
int			open_file(char *file, int *fd);
int			is_builting(t_process *prc);

/* init.c */
void		init_minishell(t_shell **all, char **envp);
void		init_pikes(t_shell **all);
void		free_pikes(t_shell **all);

/* auxiliar_functions.c */
int			is_builting(t_process *prc);
int			is_rd(int inout);
int			is_rdp(char *str);
void		close_pipes(t_shell *all);
void		close_fds(t_shell *all);

/* auxiliar_functions2.c */

int			has_quotes2(char *str);

/* expansor.c */
char		*expand_single_var(char **variable_name, t_shell *shell);
char		*expansor(t_shell *shell, char *str, int i, int j);
char		*get_env(char *str, t_env_lst *env);

/* expansor_utils.c */
char		*ft_strjoinfree(char *s1, char const *s2);
char		*ft_strjoin_char(char *s1, char c);

/* signals.c */

void		handle_signal(int signo);
void		set_signals(int mode);
void		proc_handle_signal(int sig);


// G_EXIT_STATUS
void		change_status(int new_status);

// ENVP LIST
void		fill_init_env_list(t_paths *paths, char **envp, int equal);
t_env_lst	*find_env_node(t_env_lst *env_lst, char *key);
t_env_lst	*add_env_node(t_env_lst *head, char *name, char *value, int equal);
t_env_lst	*duplicate_lst(const t_env_lst *head);
t_env_lst	*duplicate_env_node(const t_env_lst *node);
t_env_lst	*add_env_node(t_env_lst *head, char *name, char *value, int equal);
void		ft_lstdelone_env(t_env_lst *lst);
void		ft_lstclear_env(t_env_lst **lst);
void		delete_env_value(t_env_lst *lst, char *key);
void		print_env_list(t_env_lst *head);

// SORT ENV_LST
t_env_lst	*insert_sorted(t_env_lst *head, char *name, char *value, int equal);
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
void		update_or_process(t_paths *paths, char *name, char *value,
				int equal);
int			extract_name_value(char *arg, char **name, char **value);

// BUILTINS
void		ft_env(t_paths *paths, char **argv);
void		ft_cd(t_paths *paths, char **dir);
int			ft_pwd(void);
int			ft_echo(char **argv, t_process *prc);
void		ft_export(t_paths *paths, char **argv, int i);
void		ft_exit(t_shell *shell, char *line);
void		ft_unset(t_paths *paths, char **argv);

// PROMPT
char		*get_prompt(void);
char		*ft_strchrt(char *s, char c, int times);

// BUILTINS UTILS
int			arg_counter(char **argv);
char		**add_word(t_split *params);
int			quoted_len(char *s, char c);
void		handle_variable(char **token, t_paths *paths);
void		handle_exit_status(char **token);
int			remove_char(char *str, char c);
int			quotes_counter(char *str);
int			count_words(char const *s);

// PARSER

char		**echo_split(char *s, char c);
void		remove_quotes_from_string(char *str);
void		remove_quotes_from_matrix(char **matrix);

// HISTORY
void		add_to_history(t_shell *shell, const char *line);
void		print_history(t_shell *shell);
void		close_file(int fd);
void		error_exit(void);
int			open_history_file(const char *filename, int flags, int mode);

#endif
