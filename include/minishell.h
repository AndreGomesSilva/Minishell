/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2024/01/18 21:37:24 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifdef __cplusplus
extern "C" {
#endif

# include "../libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
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
};

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
	enum e_type_cmd	type;
	int				infile;
	int				outfile;
	struct s_arg	*list_args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_control
{
	char			**env;
	char			*pwd_initial;
	char			*user;
	char			*prompt;
	struct s_cmd	*cmd;
}					t_control;

/// handle_nodes
void				create_node(t_control *control, enum e_type_cmd type);
void				create_node_cmd(t_control *control, char *cmd);
void				create_node_arg(t_cmd *cmd_node, const char *arg);
t_cmd				*get_last_node(t_cmd *cmd);
int					list_len(t_cmd *lst);
void				free_cmd(t_control *control);

/// handle_parser
void				free_matrix(char **matrix);
void				handle_parser(t_control *control);

///	handle_lexer
void				print_lst(t_cmd *cmd); // FIX: retirar, função auxiliar
int					is_space(char c);
int					str_len_token(char *str, int type);
enum e_type_cmd		is_cmd(char *actual);
enum e_type_arg		is_arg(char *actual);
int					middleware(t_control *control);
char				*handle_token(t_control *control, char *input);
void				handle_signal(void);
void				handle_config(t_control **control, char **env);
int					receive_signal_ctrl_d(t_control *control);
t_cmd				*get_last_node_cmd(t_cmd *cmd);
t_arg				*get_last_node_arg(t_arg *cmd);
enum e_type_arg 	set_type_args(char *str);

/// handle_expander
void				handle_expander(t_control *control, char **env);
char	*get_var_double_quote(t_control *control,
							t_arg *double_quote_arg);
int					handle_quotes(char *str);
char				*get_var(const char *var, char **env);
int					is_variable(char *str);

#endif

#ifdef __cplusplus
} // extern "C"
#endif