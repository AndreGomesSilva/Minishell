#include "../../include/minishell.h"

int	str_len_token(const char *str, int delimiter)
{
	int	i;

	i = 0;
	if (delimiter == QUOTE)
	{
		str++;
		while (str[i] && str[i] != '\'' && str[i] != '"')
			i++;
		return (i + 2);
	}
	else if (delimiter == RE_HERD)
	{
		if (str[i] && str[i] == '<' && str[i + 1] == '<')
			i = i + 2;
		else if (str[i] && str[i] == '>' && str[i + 1] == '>')
			i = i + 2;
		if (str[i] && str[i] == '<' || str[i] == '>')
			i++;
		return (i);
	}
	else if (!delimiter)
		while (str[i] && !is_delimiter(str[i]) && !is_space(str[i]))
			i++;
	return (i);
}

//void	create_args(t_control *control, char *input, int size_cmd)
//{
//}

char	*create_cmd(t_control *control, char *actual, int type_cmd,
		int *size_cmd)
{
	t_cmd	*last_cmd;
	int		len;

	len = 0;
	len = str_len_token(actual, is_delimiter(*actual));
	create_cmd_node(control, ft_substr(actual, 0, len));
	last_cmd = get_last_node_cmd(control->cmd);
	last_cmd->type = type_cmd;
	return (actual + len);
}

char	*split_token(t_control *control, char *input)
{
	char	*actual;
	int		type_cmd;
	int		size_cmd;

	actual = input;
	size_cmd = 0;
	while (*actual)
	{
		type_cmd = is_cmd(actual);
		if (type_cmd)
		{
//			create_node_cmd(control);
			actual = create_cmd(control, actual, type_cmd, &size_cmd);
//			create_args(control, actual, size_cmd);
			size_cmd = 0;
		}
		actual++;
		size_cmd++;
	}
}

int	handle_token(t_control *control)
{
	char	*input;

	input = readline(control->prompt);
	if (input)
	{
		add_history(input);
		while (*input)
		{
			while (is_space(*input))
				input++;
			if (*input && ft_isascii(*input))
				input = split_token(control, input);
			else if (*input)
				input++;
		}
		free(input);
		return (TRUE);
	}
	else
		receive_signal_ctrl_d(control);
	return (FALSE);
}
