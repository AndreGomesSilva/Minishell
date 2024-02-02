#include "../../include/minishell.h"

// FIX: retirar posteriormente, função auxiliar

void	print_lst(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	printf("number of nodes: %d\n", list_len(cmd));
	printf("\n---------------------------------\n");
	while (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		printf("CMD: %s --- type: %d -- delimiter_type: %d \n", ptr_cmd->cmd,
			ptr_cmd->type, ptr_cmd->delimiter_type);
		while (ptr_arg)
		{
			printf("ARG: %s --- type: %d \n", ptr_arg->arg, ptr_arg->type);
			ptr_arg = ptr_arg->next;
		}
		printf("\n---------------------------------\n");
		ptr_cmd = ptr_cmd->next;
	}
}

char	*create_arg(t_cmd *cmd, char *input)
{
	t_arg	*last_arg;
	int		len;

	len = 0;
	while (is_space(*input))
		input++;
	if (*input != '|')
	{
		len = get_token_len(input, is_arg(input));
		create_node_arg(cmd, ft_substr(input, 0, len));
		last_arg = get_last_node_arg(cmd->list_args);
		last_arg->type = is_arg(last_arg->arg);
	}
	input = input + len;
	while (is_space(*input))
		input++;
	return (input);
}

char	*create_cmd(t_control *control, char *actual)
{
	int		len;
	t_cmd	*node;

	len = 0;
	while (is_space(*actual))
		actual++;
	if (!*actual)
		return (actual);
	if (*actual == '|')
		create_node_cmd(control, (char *)"");
	else
	{
		len = get_token_len(actual, is_arg(actual));
		create_node_cmd(control, ft_substr(actual, 0, len));
		node = get_last_node_cmd(control->cmd);
		node->type = is_arg(node->cmd);
	}
	actual = actual + len;
	while (is_space(*actual))
		actual++;
	return (actual);
}

void	handle_token(t_control *control, char *input)
{
	char			*actual;

	actual = input;
	while (*actual)
	{
		actual = create_cmd(control, actual);
		while (*actual)
		{
			if (*actual == '|')
			{
				get_last_node_cmd(control->cmd)->delimiter_type = PIP;
				actual++;
				break ;
			}
			else
				actual = create_arg(get_last_node_cmd(control->cmd), actual);
		}
	}
}
