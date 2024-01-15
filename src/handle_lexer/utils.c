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
	if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '>' || c == '<')
		return (REDIRECT_HERD);
	else
		return (NILL);
}

int	is_args(char *actual)
{
	if (!actual || !*actual)
		return (NORM);
	else if (*actual == '<')
	{
		if (*(actual + 1) == '<')
			return (REDIRECT_HERD);
		else
		 	return (REDIRECT_INPUT);
	}
	else if (*actual == '>')
	{
		if (*(actual + 1) == '>')
			return (REDIRECT_OUTPUT_APPEND);
		else
		 	return (REDIRECT_OUTPUT);
	}
	else if (*actual == '$')
		return (VAR_EXPAND);
	else if (*actual == '\'')
		return (QUOTE);
	else if (*actual == '\"')
		return (DOUBLE_QUOTE);
	else 
		return (NORM);
}

//0 = false, 1 = pipe, 2 = or, 3 = and
int	is_cmd(char *actual)
{
	int	i;

	i = 0;
	if (!actual || !*actual)
		return (NILL);
	else if (actual[i] == '|')
			return (PIP);
	else
		return (NILL);
}
