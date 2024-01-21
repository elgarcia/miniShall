#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "structures.h"

/* parser.c */
int			input_parser(char *line, t_shell *new); //split del input
// int		check_process(t_shell *new); //comprueba que los procesos sean validos
void		check_redaux(char *in, t_process *aux, int *i); //red checks
void		check_red(char *in, char *in2, t_process **aux, int *i); //red checks

/* utils.c*/
void		ft_free(char **arg, int size);
int			ft_word_count(const char *s1, char delimiter);
void		*free_null(char **s);
char		*ft_strjoinup(char **s1, char *s2);

/* executor.c */
void		exec_process(t_shell *all);

/* pr_checker.c */
int			check_builtins(t_process **prcs, t_shell *all);
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
void		open_file(char *file, int *fd, int *pipe_fd);
void		treat_fork(int *pipes, char *argv, char ***exec_args, t_env_lst *envp);
int			treat_single(char *argv, char ***exec_args, t_env_lst *envp, int *pipe);

/* init.c */
void		init_minishell(t_shell **all);
void		init_pikes(t_shell **all);
void		free_pikes(t_shell **all);
void		free_pipes(t_shell *all, int ***pipes, int n_pipes);

// ENVP LIST
void		fill_init_env_list(t_paths *paths, char **envp);
t_env_lst	*find_env_node(t_env_lst *env_lst, char *key);
t_env_lst	*add_env_node(t_env_lst *head, \
			char *name, char *value, int equal);
void		ft_lstdelone_env(t_env_lst *lst);
void		ft_lstclear_env(t_env_lst **lst);
void		delete_env_value(t_env_lst *lst, char *key);
void		print_env_list(t_env_lst *head);

// BUILTINS
void		ft_env(t_paths *paths);
void		ft_cd(t_paths *paths, char *dir);
int			ft_pwd(void);
int			ft_echo(char **argv);
void		ft_export(t_paths *paths, char **argv, int i);
void		ft_exit(t_shell *shell);

#endif
