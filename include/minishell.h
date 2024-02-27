/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/27 00:24:49 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #ifdef __cplusplus
// extern "C" {
// #endif

# include <stdio.h>
# include "../libft/include/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define INT_MIN (-2147483648)

enum					e_type_cmd
{
	NILL,
	PIP
};

enum					e_type_arg
{
	NORM,
	VAR_EXPAND,
	BROKEN_QUOTES,
	REDIRECT_HERD,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND,
	IOFILE,
	DOC,
};

enum					e_type_builtin
{
	B_NOBT,
	B_ECHO,
	B_CD,
	B_PWD,
	B_ENV,
	B_EXPORT,
	B_UNSET,
	B_EXIT
};

enum					e_type_error
{
	E_NO_ERROR,
	E_CMD_NO_FOUND,
	E_NO_FILE,
	E_PERMISSION,
	E_FATAL,
	E_SYNTAX,
	E_EXPORT,
	E_UNSET
};

typedef struct s_ht_item
{
	char				*key;
	char				*value;
	int					type_print;
	struct s_ht_item	*next;
}						t_ht_item;

typedef struct s_table
{
	int					count;
	int					size;
	struct s_ht_item	**items;
}						t_table;

typedef struct s_arg
{
	char				*arg;
	enum e_type_arg		type;
	struct s_arg		*next;
}						t_arg;

typedef struct s_cmd
{
	char				*cmd;
	char				**cmd_and_args;
	char				*path_cmd;
	enum e_type_arg		type;
	enum e_type_cmd		delimiter_type;
	enum e_type_error	error_type;
	int					infile;
	int					outfile;
	int					cmd_number;
	char				*heredoc_file;
	struct s_arg		*list_args;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_control
{
	t_table				*env_table;
	char				**env;
	char				*prompt;
	struct s_cmd		*cmd_actual;
	struct s_cmd		*cmd;
	int					**pipe_fd;
	pid_t 				*pid;
	int					status_cmd;
	int					fatal_err;
	int					n_pipes;
}						t_control;

//	common
void					free_control(t_control *control);
t_ht_item				*free_node(t_ht_item *node);
int						print_error(t_cmd *ptr_cmd, enum e_type_error error);
void					handle_config(t_control **control, char **env);
void					handle_signal(void);
int						receive_signal_ctrl_d(t_control *control);
int						ctrl_d_herdoc(t_control *control, char *eof);
void					get_input(t_control *control);
void					set_path(t_control *control);
void					ctrl_c_heredoc(int sig);

// handle_nodes
void					create_node_cmd(t_control *control, char *cmd);
void					create_node_arg(t_cmd *cmd_node, const char *arg);
int						list_len(t_cmd *lst);
t_cmd					*get_last_node_cmd(t_cmd *cmd);
t_arg					*get_last_node_arg(t_arg *cmd);
void					free_cmd(t_control *control);

// handle_parser
int						is_valid_cmd(t_cmd *cmd);
void					free_matrix(char **matrix);
char					*handle_bin_path(t_control *control, char *cmd);
int						is_builtin(char *cmd);
void					handle_parser(t_control *control);
int						handle_syntax_error(t_cmd *cmd);
int						is_absolute_path(char *cmd);

//	handle_lexer
char					*swap_string(char *str, char *sub_str);
int						verify_broken_quote(t_control *control);
void					handle_quotes_parsing(t_control *control);
int						str_compare(char *s1, char *s2);
char					*get_next_eof(t_cmd *cmd);
char					*remove_quotes(char *str);
void					infinit_prompt(t_control *control);
int						handle_quote_eof(char *eof);
int						find_heredoc_arg(t_cmd *cmd);
int						find_heredoc_cmd(t_cmd *cmd);
int						handle_heredoc(t_control *control);
void					print_lst(t_cmd *cmd);
int						is_space(char c);
int						get_token_len(char *str, int type);
enum e_type_arg			is_arg(char *actual);
void					handle_token(t_control *control, char *input);
enum e_type_arg			set_type(char *str);
int						len_string_token(char *str);
char					*create_cmd(t_control *control, char *actual);
char					*create_arg(t_cmd *cmd, char *input);
int						handle_quotes(char *str, int *iterator, int *n_quotes,
							int *flag_var);

// handle_expander

char					*expand_var(t_control *control, int *i, char *str);
char					*ft_join_var(int *i, char *str, char *var, char *end);
int						is_exit_variable(char *str);
int						look_exit_variabel(t_cmd *cmd, int flag);
char					*get_var_in_node(t_control *control, char *str);
int						handle_expander(t_control *control);
int						is_variable(char *str);
char					*handle_home_path(t_control *control, char *path);

// hashtable
void					update_matrix_env(t_control *control);
int						handle_env(t_control *control, char **env);
t_ht_item				*get_var_node(t_control *control, char *key);
char					*get_var_env(t_control *control, const char *key);
int						hash_function(const char *str, int size);
int						ft_pow(int base, int exponent);
void					free_env(t_table *table);
int						get_size_matrix(char **env);
int						get_size_env_key(const char *str);
t_table					*init_table(char **env);
void					copy_env(t_control *control, char **env);
void					print_env(t_table *table);
void					print_sort_env(t_control *control);
void					sort_matrix(char *arr[], int start, int end);
void					update_env(t_control *control, const char *key,
							const char *value, int type_print);
void					remove_env(t_control *control, const char *key);
t_ht_item				*create_hash_node(const char *key, const char *value);

// builtin
int						handle_builtin(char **cmd, t_control *control);
void					handle_cd_builtin(t_control *control, char **cmd);
void					handle_export_builtin(t_control *control, char **cmd);
void					handle_unset_builtin(t_control *control, char **cmd);
void					handle_env_builtin(t_control *control, char **cmd);
void					handle_exit_builtin(t_control *control, char **cmd);
void					handle_echo_builtin(t_control *control, char **cmd);
void					handle_pwd_builtin(t_control *control);
int						is_valid_env_name(char *str);

// executor
int						count_pipes(t_cmd *cmd);
int						**create_pipes(int n_pipes);
void					free_pipes(int **pipe_fd, int n_pipes);
void					close_pipes(int **pipe_fd, int n_pipes);
void					handle_execution(t_control *control);
char					*get_last_outfile(t_cmd *cmd);
char					*get_last_infile(t_cmd *cmd);
int						handle_io(t_cmd *cmd, int **pipe_fd, int index,
							int multi_cmd);
void					close_fd(int in, int out);
void					change_stdio(int in, int out);

#endif

// #ifdef __cplusplus
// } // extern "C"
// #endif