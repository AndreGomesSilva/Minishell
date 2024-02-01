#include "../include/minishell.h"

int	middleware(t_control *control)
{
	char *input;
	char *first_input;

	input = readline(control->prompt);
	first_input = input;
	if (input)
	{
		add_history(input);
		while (is_space(*input))
			input++;
		if (*input)
		handle_token(control, input);
			handle_expander(control);
		handle_parser(control);
		print_lst(control->cmd);
		free(first_input);
		free_cmd(control);
		return (TRUE);
	}
	else
		receive_signal_ctrl_d(control);
	return (FALSE);
}
