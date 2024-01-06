//
// Created by angomes- on 12/5/23.
//

#include "../../include/minishell.h"

//
static void	create_token(t_control *control, char *input)
{
	while (*input)
	{
		while (is_space(*input))
			input++;
		if (*input && ft_isascii(*input))
			input = split_token(control, input);
		else if (*input)
			input++;
	}
}

int	handle_ctrl_d(t_control *control)
{
	clear_history();
	free_cmd(control);
	exit(0);
}

int	handle_token(t_control *control)
{
	char *input;

	input = readline(control->prompt);
	if (input)
	{
		add_history(input);
		create_token(control, input);
		free(input);
		return (TRUE);
	}
	else
		handle_ctrl_d(control);
	return (FALSE);
}