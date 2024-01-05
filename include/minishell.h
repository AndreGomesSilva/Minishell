/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2024/01/04 12:43:29 by r-afonso         ###   ########.fr       */
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

enum e_type
{
	CMD,
	VAR,
	PIP,
	RED,
	HER,
};

typedef struct s_args
{
	char			*token;
	enum e_type 	type;
	char 			*value;
	struct s_lst	*next;
}					t_lst;

typedef struct s_cmd
{
	char 			*cmd;
	char 			**full_cmd;
	char 			**path_cmd;
	int 			infile;
	int 			outfile;
	struct s_lst	*lst_cmd;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_control
{

	char 			*pwd;
	char 			*user;
	char			*prompt;
	struct s_cmd	*cmd;
}					t_control;

/// handle_nodes
void				create_node(t_control *control, char *cmd);
int					list_len(t_lst *lst);
void				free_lst(t_control *control);
/// handle_matrix
void				free_matrix(char **matrix);

///	handle_lexer
int 				is_space(char c);
int					is_delimiter(char c);
void				set_type(t_lst *lst);
int				handle_token(t_control *control);
void				handle_signal(void);
void				handle_start(t_control **control, char **env);

/// handle_expander
void handle_expander(t_control *control, char **env);
char *get_var(char *var, char **env);

#endif
