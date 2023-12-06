//
// Created by angomes- on 12/5/23.
//

#include "../../include/minishell.h"

static void	create_token(t_lst **lst, char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
	{
		create_main_node(lst, strdup(matrix[i]));
		i++;
	}
	free_matrix(matrix);
}

void	token_factory(t_lst **lst, char **matrix)
{
	create_token(lst, matrix);
}