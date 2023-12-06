/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2023/12/05 14:40:36 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0

# include "../libft/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_lst
{
	char			*token_name;
	int				priority;
	char			**args;
	struct s_lst	*next;
	struct s_lst	*previous;
}	t_lst;

typedef struct s_aux
{
	int				max_priority;
	struct s_lst	*target_priority;
}	t_aux;


/// handle_nodes
void	create_main_node(t_lst **lst, char *cmd);
int		list_len(t_lst **lst);
void	free_lst(t_lst **lst);

/// test
int		func_test(void);

/// handle_matrix
void	free_matrix(char **matrix);

//	handle_lexer
void	token_factory(t_lst **lst, char **matrix);

#endif
