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
	else if (*actual == '$')
		return (VAR_EXPAND);
	else if (*actual == '"' || *actual == '\'')
	{
		while (actual++, *actual)
		{
			if (*actual == '"')
				return (DOUBLE_QUOTE);
			else if (*actual == '\'')
				return (QUOTE);
		}
	}
	return (NORM);
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
	int	i;

	i = 0;
	if ((type == QUOTE || type == DOUBLE_QUOTE) && ++str)
	{
		if (type == DOUBLE_QUOTE)
			while (str[i] && str[i] != '"')
				i++;
		else
			while (str[i] && str[i] != '\'')
				i++;
		return (i + 2);
	}
	else if (type == REDIRECT_HERD)
	{
		if (str[i] && (((str[i] == '<' && str[i + 1] == '<')) || ((str[i] == '>') && (str[i + 1] == '>'))))
			i = i + 2;
		else if (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
	}
	else if (!type)
		while (str[i] && ((!is_arg(&str[i]) || is_arg(&str[i]) == VAR_EXPAND))
			&& !is_space(str[i]))
			i++;
	return (i);
}