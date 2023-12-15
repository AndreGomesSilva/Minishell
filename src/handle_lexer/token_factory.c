//
// Created by angomes- on 12/5/23.
//

#include "../../include/minishell.h"

int	str_len_token(const char *str, int delimiter)
{
	int i;

	i = 0;
	str++;
	while (str[i] && str[i] != delimiter)
		i++;
	return (i);
}

static int		split_token(t_control *control, char *input, char *begin)
{
	int len;
	char *ptr;

	len = 0;
	ptr = begin;
	if (*begin == '\'')
	{
		ptr++;
		while (*ptr && *ptr != '\'')
			ptr++;
		if (!*ptr || *(begin + 1) == '\'')
			create_node(control, strdup(""));
		else
		{
			len = str_len_token(begin, '\'');
			create_node(control, ft_substr(begin, 0, len + 2));
		}
	}
	else
		create_node(control, strdup(""));
	return (len);
}

static void		create_token(t_control *control, char *input)
{
		char *begin;
		char *ptr;
		int len;

		if (!input)
			return ;
		len = 0;
		begin = input;
		ptr = begin;
		while (*ptr)
		{
			if (*ptr == '\'')
			{
				begin = ptr;
				len = split_token(control, input, begin);
				ptr = ptr + len + 2;
			}
			else
				ptr++;
		}
}

//static void	create_token(t_control *control, char **matrix)
//{
//	int	i;
//
//	i = 0;
//	while (matrix[i])
//		create_node(control, ft_strdup(matrix[i++]));
//	free_matrix(matrix);
//}

int handle_ctrl_d(t_control *control)
{
	clear_history();
	free_lst(control);
	exit(0);
}

int	take_input(t_control *control)
{
	char	**input_matrix;
	char	*input;

	input = readline("> ");	
	if (input)
	{
//		input_matrix = ft_split(input, ' ');
		add_history(input);
//		handle_token(control, input_matrix);
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
//	create_token(control, matrix);
}
