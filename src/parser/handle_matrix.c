//
// Created by angomes- on 12/5/23.
//

#include "../../include/minishell.h"

void	free_matrix(char **matrix)
{
	char **ptr_temp;

	ptr_temp = matrix;
	while (*matrix)
	{
		free(*matrix);
		matrix++;
	}
	free(ptr_temp);
}