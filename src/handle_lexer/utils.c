#include "../../include/minishell.h"

int	receive_signal_ctrl_d(t_control *control)
{
	clear_history();
	free_cmd(control);
	exit(0);
}

int	is_space(char c)
{
	if (c != 0 && c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

int	is_delimiter(char c)
{
	if (c == '\'' || c == '"')
		return (QUOTE);
	else if (c == '>' || c == '<')
		return (RE_HERD);
	// else if (c == '|')
	// 	return (3);
	else
		return (NILL);
}

//int	is_args(t_control *control, char *actual)
//{
//}

//0 = false, 1 = pipe, 2 = or, 3 = and
int	is_cmd(char *actual)
{
	int	i;

	i = 0;
	if (!actual || !*actual)
		return (NILL);
	else if (actual[i] == '|')
		if (actual[i + 1] == '|')
			return (OR);
		else
			return (PIP);
	else if (actual[i] == '&' && actual[i + 1] == '&')
		return (AND);
	else
		return (NILL);
}
