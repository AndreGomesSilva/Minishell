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

int	take_input(t_lst **lst)
{
	char	**input_matrix;
	char	*input;

	input = readline("> ");
	if (input)
	{
		input_matrix = ft_split(input, ' ');
		add_history(input);
		token_factory(lst, input_matrix);
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

void	token_factory(t_lst **lst, char **matrix)
{
	create_token(lst, matrix);
}