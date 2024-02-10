/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/10 00:09:11 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #ifdef __cplusplus
// extern "C" {
// #endif

# include "../libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

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
	NOBT,
	ECHO,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT
};

enum					e_type_error
{
	NO_ERROR,
	CMD_NO_FOUND,
	NO_FILE,
	FATAL,
	SYNTAX,
};

typedef struct s_ht_item
{
	char				*key;
	char				*value;
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
	struct s_arg		*list_args;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_control
{
	t_table				*env_table;
	char				**env;
	char				*user;
	char				*prompt;
	struct s_cmd		*cmd;
}						t_control;

//	common

void					free_control(t_control *control);
t_ht_item				*free_node(t_ht_item *node);
void					handle_error(t_cmd *ptr_cmd, enum e_type_error error);
void					handle_config(t_control **control, char **env);
void					handle_signal(void);
int						receive_signal_ctrl_d(t_control *control);
int						middleware(t_control *control);

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
char					*handle_bin_path(t_control *control, t_cmd *cmd);
int						is_builtin(char *cmd);
int						handle_parser(t_control *control);
int						handle_syntax_error(t_cmd *cmd);
int						is_absolute_path(char *cmd);

//	handle_lexer
int						search_heredoc_arg(t_cmd *cmd);
int						search_heredoc_cmd(t_cmd *cmd);
void					handle_heredoc(t_control *control);
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
int						handle_expander(t_control *control);
int						is_variable(char *str);
char					*handle_home_path(t_control *control, char *path);

// hashtable
int						handle_envp(t_control *control, char **env);
t_ht_item				*get_var_node(t_control *control, char *key);
char					*get_var(t_control *control, const char *key);
int						hash_function(const char *str, int size);
int						ft_pow(int base, int exponent);
void					free_hash_table(t_table *table);
int						len_env(char **env);
int						strlen_var_name(const char *str);
t_table					*init_table(char **env);
void					copy_env(t_control *control, char **env);
void					print_hash_table(t_table *table);
void					print_sort_env(t_control *control);
void					matrix_quicksort(char *arr[], int start, int end);
void					update_env_var(t_control *control, char *key,
							char *value);
void					remove_env_var(t_control *control, char *key);
t_ht_item				*create_hash_node(char *key, char *value);

// builtin
int						handle_builtin(char **matriz);
int						handle_cd(char **matriz);
int						handle_export(char **matriz);
int						handle_unset(char **matriz);
int						handle_env(char **matriz);
int						handle_exit(char **matriz);
int						handle_echo(char **matriz);
int						handle_pwd(char **matriz);

#endif

// #ifdef __cplusplus
// } // extern "C"
// #endif