/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2024/01/11 17:56:14 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


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
	NILL,
	PIP
};

enum				e_type_arg
{
	NORM,
	QUOTE,
	DOUBLE_QUOTE,
	VAR_EXPAND,
	REDIRECT_HERD,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND
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
	char 			**env;
	char			*pwd_initial;
	char			*user;
	char			*prompt;
	struct s_cmd	*cmd;
}					t_control;

/// handle_nodes
void				create_node(t_control *control, enum e_type_cmd type);
void				create_cmd_node(t_control *control, char *cmd);
void				create_arg_node(t_cmd *cmd_node, char *arg);
t_cmd				*get_last_node(t_cmd *cmd);
int					list_len(t_cmd *lst);
void				free_cmd(t_control *control);

/// handle_matrix
void				free_matrix(char **matrix);

///	handle_lexer
int					is_space(char c);
int					is_delimiter(char c);
int					is_cmd(char *actual);
int					is_args(char *actual);
void				set_type(t_cmd *lst);
int					handle_input(t_control *control);
char				*handle_token(t_control *control, char *input);
void				handle_signal(void);
void				handle_start(t_control **control, char **env);
int					receive_signal_ctrl_d(t_control *control);
t_cmd				*get_last_node_cmd(t_cmd *cmd);
t_arg				*get_last_node_arg(t_arg *cmd);

/// handle_expander
void				handle_expander(t_control *control, char **env);
char 				*get_var_double_quote(t_control *control, t_arg *double_quote_arg);
char				*get_var(char *var, char **env);
int 				is_variable(char *str);

#endif
