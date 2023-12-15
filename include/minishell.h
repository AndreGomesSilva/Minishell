/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2023/12/14 21:30:49 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_lst
{
	char			*token_name;
	int				priority;
	char			**args;
	struct s_lst	*next;
	struct s_lst	*previous;
}					t_lst;

typedef struct s_control
{
	struct s_lst	*lst;
}					t_control;

/// handle_nodes
void				create_node(t_control *control, char *cmd);
int					list_len(t_lst *lst);
void				free_lst(t_control *control);
/// handle_matrix
void				free_matrix(char **matrix);

///	handle_lexer
void				handle_token(t_control *control, char *input);
int					take_input(t_control *control);
void				handle_signal(void);
void				handle_start(t_control **control);

#endif
