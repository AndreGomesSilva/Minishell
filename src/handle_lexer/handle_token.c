#include "../../include/minishell.h"

int	str_len_token(const char *str, int delimiter)
{
	int	i;

	i = 0;
	if (delimiter == QUOTE || delimiter == DOUBLE_QUOTE)
	{
		str++;
		if (delimiter == DOUBLE_QUOTE)
			while (str[i] && str[i] != '"')
				i++;
		else
			while (str[i] && str[i] != '\'')
				i++;
		return (i + 2);
	}
	else if (delimiter == REDIRECT_HERD)
	{
		if (str[i] && (str[i] == '<' && str[i + 1] == '<')
			|| (str[i] && str[i] == '>' && str[i + 1] == '>'))
			i = i + 2;
		else if (str[i] && str[i] == '<' || str[i] == '>')
			i++;
	}
	else if (!delimiter)
		while (str[i] && !is_delimiter(str[i]) && !is_space(str[i]))
			i++;
	return (i);
}

char	*create_args(t_cmd *cmd, char *input)
{
	t_arg	*last_arg;
	int		len;

	len = 0;
	while (is_space(*input))
		input++;
	if (!is_cmd(input) && (is_args(input) == QUOTE || is_args(input) == VAR_EXPAND || is_args(input) == NORM) || is_args(input) == DOUBLE_QUOTE)
	{
		len = str_len_token(input, is_delimiter(*input));
		create_arg_node(cmd, ft_substr(input, 0, len));
		last_arg = get_last_node_arg(cmd->list_args);
		last_arg->type = is_args(last_arg->arg);
	}else {
		create_arg_node(cmd, "");
		get_last_node_arg(cmd->list_args)->type = is_args(input);
		if (is_args(input) == REDIRECT_INPUT || is_args(input) == REDIRECT_OUTPUT)
			len += 1;
		else
		 	len += 2;
	}
	input = input + len;
	while (is_space(*input))
		input++;
	return (input);
}

char	*create_cmd(t_control *control, char *actual)
{
	int	len;

	len = 0;
	while (is_space(*actual))
		actual++;
	if (is_cmd(actual) || is_args(actual))
		create_cmd_node(control, "");
	else
	{
		len = str_len_token(actual, is_delimiter(*actual));
		create_cmd_node(control, ft_substr(actual, 0, len));
	}
	return (actual + len);
} 

char	*handle_token(t_control *control, char *input)
{
	char	*actual;
	int		result_is_cmd;

	actual = input;
	while (*actual)
	{
		actual = create_cmd(control, actual);
		while (*actual)
		{
			result_is_cmd = is_cmd(actual);
			if (result_is_cmd)
			{
				get_last_node_cmd(control->cmd)->type = result_is_cmd;
				if (result_is_cmd == PIP)
					actual++;
				else
					actual += 2;
				break ;
			}
			else
				actual = create_args(get_last_node_cmd(control->cmd), actual);
		}
	}
	return (actual);
}
