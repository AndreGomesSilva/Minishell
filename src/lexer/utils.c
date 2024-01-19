#include "../../include/minishell.h"

int	is_space(char c)
{
	if (c != 0 && (c == ' ' || c == '\t'))
		return (TRUE);
	return (FALSE);
}

enum e_type_arg	is_arg(char *actual)
{
	if (!actual || !*actual)
		return (NORM);
	if (*actual == '<')
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
	return(set_type_args(actual));
}

//0 = false, 1 = pipe, 2 = or, 3 = and
enum e_type_cmd	is_cmd(char *actual)
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

int	str_len_token(char *str, int type)
{
	int	len;

	len = 0;
	if (type == REDIRECT_HERD)
	{
		if (str[len] && (((str[len] == '<' && str[len + 1] == '<')) || ((str[len] == '>') && (str[len + 1] == '>'))))
			len = len + 2;
		else if (str[len] && (str[len] == '<' || str[len] == '>'))
			len++;
	}
	else
		if (str[len] && ((is_arg(&str[len]) <= BROKEN_QUOTES)))
			len = handle_quotes(str);
	return (len);
}