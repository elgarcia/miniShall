/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:53:39 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/22 11:30:20 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "structures.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define RED_TEXT "\001\033[1;31m\002"
# define GREEN_TEXT "\001\033[1;32m\002"
# define YELLOW_TEXT "\001\033[1;33m\002"
# define RESET_TEXT "\001\033[0m\002"
# define BLUE_TEXT "\001\e[0;34m\002"

/* parser.c */
int			input_parser(char *line, t_shell *new, int i);
void		check_redaux(char **in, t_process **aux, int *i, t_redir **red_aux);
void		check_red(char **in, t_process **aux, int *i, t_redir **red_aux);
void		new_proc(t_process **aux, t_shell *all, int n_proc,
				t_redir **red_aux);
void		parse_arg(t_process **aux, t_shell *new, int *i, t_redir *red_aux);

/* parser_aux.c */
void		assign_redir(t_process **aux, int *i, t_redir **red_aux,
				int rd_type);
int			is_ao(char *str);
int			check_cats(t_shell *all, t_process *aux);
void		check_exp(char **in, int *i, int j);
int			there_is_rd(t_process *lst);

/* parser_aux_2.c */
int			separate_rd(char ***input, int i, int aux);
char		**ft_reallocate(char ***in, int size, int pos, char *rd);

/* utils.c*/
void		ft_free(char ***arg, int size);
int			ft_word_count(const char *s1, char delimiter);
int			ft_strcmp(char *s1, char *s2);
void		*free_null(char **s);
char		*ft_strjoinup(char **s1, char *s2);
void		*malloc_safe(int num_elements, int size);

/* utils_2.c */
int			ft_strlenchr(const char *s, char c);
char		**list_to_array(t_env_lst *env);
void		check_status(t_shell *shell, int status);

/* envp.c */
void		replace_envp(char *name, char *value, char **envp);

/* executor.c */
void		exec_process(t_shell *all, int i, int j, int status);
void		close_pipes(t_shell *all);
int			exec_type(t_shell *all, t_process *aux, int hd);
void		here_doc(t_shell *all, t_process *aux, int rd);
void		exec_son(t_shell *all, t_process *aux);

/* executor_aux.c */
void		reset_prc(t_shell *all);
void		pipe_man(t_shell *all);
void		init_executor(t_shell *all, t_process **aux, int *i, int *j);
void		read_file(t_shell *all, t_process *prc, char *line, char *outword);
int			count_rds(t_process *prcs);

/* executor_aux2.c */
int			search_rd(t_process *prc, int rd, int rd2);
int			is_rd_ch(char ch);
void		trim_outword(char *outword);
void		read_loop(t_shell *all, int fd_aux, char **line, char **split);

/* executor_aux3.c */
int			appnd_rd(t_shell *all, char **file);
int			in_rd(t_shell *all, char **file);
void		rd_file(t_shell *all, int fd_aux, char **split, int *mypipe);
int			check_quoted_string(char **command);
/* pr_checker.c */
int			check_builtins(t_shell *all, t_process *aux);
int			check_command(t_shell *all, t_process **prcs, char ***exec_args);
char		*get_ifile(char *process, int inout);

/* pr_checker_aux.c */
char		*get_commad(t_process *prc, char **split);
void		free_prcs(t_shell *all);
void		execute_builtin(t_shell *all, t_process *prc);

/* command_aux.c */
int			search_path(char **env_1, char **actual_path, char *command,
				char ***exec_args);
int			init_execargs(char ***ex_argc, char *command);

/* commands.c */
int			check_cmd(char **command, char ***exec_args);
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
void		write_file(t_shell *all, int fd, char *line);
int			skip_quotes(char *str, int i, int j);
int			check_file(char **file, t_process *aux, t_redir *i);
void		ft_allocate(int comp, int *size, char ***aux, size_t len);

/* expansor.c */
char		*expand_single_var(char **variable_name, t_shell *shell);
char		*expansor(t_shell *shell, char *str, int i);
char		*get_env(t_shell *shell, char *str, t_env_lst *env);

/* expansor_utils.c */
char		*ft_strjoinfree(char *s1, char const *s2);
char		*ft_strjoin_char(char *s1, char c);

/* signals.c */
void		handle_signal(int signo);
void		set_signals(int mode);
void		proc_handle_signal(int sig);

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
void		ft_env(t_paths *paths);
void		ft_cd(t_paths *paths, char **dir);
int			ft_pwd(t_shell *shell);
int			ft_echo(char **argv, t_process *prc);
int			ft_export(t_paths *paths, char **argv);
void		ft_exit(t_shell *shell, char *line);
void		ft_unset(t_paths *paths, char **argv);

// PROMPT
char		*get_prompt(void);
char		*ft_strchrt(char *s, char c, int times);

// BUILTINS UTILS
int			arg_counter(char **argv);
int			remove_char(char *str, char c);
int			quotes_counter(char *str);
int			count_words(char *s);
void		clear_everything(t_shell *shell, int pikes);
void		ft_lstdelone_proc(t_process *lst);
void		ft_lstclear_pro(t_process **lst);

// PARSER
char		**split_words(char *s);
void		remove_quotes_from_string(char *str);
void		remove_quotes_from_matrix(char **matrix);

// HISTORY
void		add_to_history(t_shell *shell, const char *line);
void		print_history(t_shell *shell);
void		close_file(int fd);
void		error_exit(void);
int			open_history_file(const char *filename, int flags, int mode);

// LAST FIXES
int			find_next_quote(int i, char *str, char c);
void		exit_error(char *str);
int			check_opened_quotes(char *s, int simple, int doble);
int			check_pair_quotes(char *s, int *i, char c);
char		*ft_add_quotes(char *s);
int			ft_isspace(const char *str);
#endif
