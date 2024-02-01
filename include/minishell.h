/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/01 16:05:40 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifdef __cplusplus
extern "C" {
#endif

# include <stdio.h>
# include "../libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define INT_MIN (-2147483648)

enum				e_type_cmd
{
	NILL, // 0
	PIP   // 1
};

enum				e_type_arg
{
	NORM,                  	// 0
	VAR_EXPAND,            	// 1
	BROKEN_QUOTES,         	// 2
	REDIRECT_HERD,         	// 3 FIXME: ainda nao implementado
	REDIRECT_INPUT,        	// 4
	REDIRECT_OUTPUT,       	// 5
	REDIRECT_OUTPUT_APPEND, // 6
	IOFILE,
};

enum	e_type_builtin
{
	NOBT,                  //not a builtin
	ECHO,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
};

typedef struct s_ht_item
{
	char				*key;
	char				*value;
	struct s_ht_item	*next;
}	t_ht_item;

typedef struct s_table
{
	int					count;
	int 				size;
	struct s_ht_item	**items;
}	t_table;

typedef struct s_arg
{
	char			*arg;
	enum e_type_arg	type;
	struct s_arg	*next;
}					t_arg;

typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_and_args;
	char			*path_cmd;
	enum e_type_arg	type;
	enum e_type_cmd delimiter_type;
	int				infile;
	int				outfile;
	struct s_arg	*list_args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_control
{
	t_table			*env_table;
	char			**env;
	char			*pwd_initial;
	char			*user;
	char			*prompt;
	struct s_cmd	*cmd;
}					t_control;

// handle_nodes
void				create_node_cmd(t_control *control, char *cmd);
void				create_node_arg(t_cmd *cmd_node, const char *arg);
int					list_len(t_cmd *lst);
t_cmd				*get_last_node_cmd(t_cmd *cmd);
t_arg				*get_last_node_arg(t_arg *cmd);
void				free_cmd(t_control *control);

// handle_parser
void				free_matrix(char **matrix);
void 				handle_bin_path(t_control *control, t_cmd *cmd);
int					is_builtin(char *cmd);
void				handle_parser(t_control *control);

//	handle_lexer
void				print_lst(t_cmd *cmd); // FIX: retirar, função auxiliar
int					is_space(char c);
int					get_token_len(char *str, int type);
enum e_type_cmd		is_cmd(char *actual);
enum e_type_arg		is_arg(char *actual);
int					middleware(t_control *control);
void				handle_token(t_control *control, char *input);
void				handle_signal(void);
void				handle_config(t_control **control, char **env);
int					receive_signal_ctrl_d(t_control *control);
enum e_type_arg 	set_type(char *str);
int					len_string_token(char *str);
char				*create_cmd(t_control *control, char *actual);
char				*create_arg(t_cmd *cmd, char *input);

// handle_expander
void				handle_expander(t_control *control);
int					is_variable(char *str);
char				*handle_home_path(t_control *control, char *path);

// hashtable
int 				handle_envp(t_control *control, char **env);
t_ht_item 			*get_var_node(t_control *control, char *key);
char				*get_var(t_control *control, const char *key);
int					hash_function(const char *str, int size);
int					ft_pow(int base, int exponent);
void 				free_hash_table(t_table *table);
int					len_env(char **env);
int 				strlen_var_name(char *str);
t_table 			*init_table(t_control *control, char **env);
void				copy_env(t_control *control, char **env);
void				print_hash_table (t_table *table);

#endif

#ifdef __cplusplus
} // extern "C"
#endif