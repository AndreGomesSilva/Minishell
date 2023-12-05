/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:10:02 by r-afonso          #+#    #+#             */
/*   Updated: 2023/12/04 15:36:46 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <unistd.h>
# include <stdio.h>

<<<<<<< HEAD
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
	struct t_lst	*target_priority;
}	t_aux;


void	create_main_node(t_lst **lst, char *cmd);
int		list_len(t_lst **lst);
=======
int func_test(void);
>>>>>>> ce84393ce51829fd6ed105de30d929dde356b876

#endif //MINISHELL_MINISHELL_H
