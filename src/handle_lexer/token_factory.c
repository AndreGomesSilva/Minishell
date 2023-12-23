//
// Created by angomes- on 12/5/23.
//

#include "../include/minishell.h"

static int 	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

static int is_delimiter(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else if (c == '>' || c == '<')
		return (2);
	else if (c == '|')
		return (3);
	else
		return (0);
}

int	str_len_token(const char *str, int delimiter)
{
	int i;

	i = 0;
	if (delimiter == 1)
	{
		str++;
		while (str[i] && str[i] != '\'' && str[i] != '"')
			i++;
		return (i + 2);
	}
	else if (delimiter == 2 || delimiter == 3)
	{
		// TODO handle_here_doc
		if (str[i] && str[i] == '<' && str[i + 1] == '<')
			printf(">>Here Doc<<\n");
		if (str[i] && str[i] == '<' || str[i] == '>' || str[i] == '|')
			i++;
		return (i);
	}
	else if (!delimiter)
		while (str[i] && !is_delimiter(str[i]) && !is_space(str[i]))
			i++;
	return (i);
}

static char		*split_token(t_control *control, char *begin)
{
	int len;
	char *ptr;

	len = 0;
	ptr = begin;
	len = str_len_token(ptr, is_delimiter(*ptr));
	create_node(control, ft_substr(begin, 0, len));
	return (ptr + len);
}

static void		create_token(t_control *control, char *input)
{
		char *ptr;

		if (!input)
			return ;
		ptr = input;
		while (*ptr)
		{
			while (*ptr && is_space(*ptr))
				ptr++;
			if (*ptr && isascii(*ptr))
				ptr = split_token(control, ptr);
			else if (*ptr)
				ptr++;
		}
}

int handle_ctrl_d(t_control *control)
{
	clear_history();
	free_lst(control);
	exit(0);
}

int	take_input(t_control *control)
{
	char	*input;

	input = readline(control->prompt);
	if (input)
	{
		add_history(input);
		handle_token(control, input);
		free(input);
		return (TRUE);
	}
	else
		handle_ctrl_d(control);
	return (FALSE);
}

void	handle_token(t_control *control, char *input)
{
	create_token(control, input);
}
