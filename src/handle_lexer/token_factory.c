//
// Created by angomes- on 12/5/23.
//

#include "../../include/minishell.h"

static void	create_token(t_control *control, char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		create_node(control, ft_strdup(matrix[i++]));
	free_matrix(matrix);
}

int	take_input(t_control *control)
{
	char	**input_matrix;
	char	*input;

	input = readline("> ");
	if (input)
	{
		input_matrix = ft_split(input, ' ');
		add_history(input);
		handle_token(control, input_matrix);
		free(input);
		return (true);
	}
	return (false);
}

void	handle_token(t_control *control, char **matrix)
{
	create_token(control, matrix);
}