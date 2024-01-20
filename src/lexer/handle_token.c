#include "../../include/minishell.h"

// FIX: retirar posteriormente, função auxiliar
void	print_lst(t_cmd *cmd)
{
	printf("number of nodes: %d\n", list_len(cmd));
	printf("\n---------------------------------\n");
	while (cmd)
	{
		printf("CMD: %s --- type: %d -- delimiter_type: %d \n", cmd->cmd, cmd->type, cmd->delimiter_type);
		while (cmd->list_args)
		{
			printf("ARG: %s --- type: %d \n", cmd->list_args->arg,
					cmd->list_args->type);
			cmd->list_args = cmd->list_args->next;
		}
		printf("\n---------------------------------\n");
		cmd = cmd->next;
	}
}

//char	*handle_redirect(const enum e_type_arg type, int len, t_cmd *cmd,
//		char *input)
//{
//	create_node_arg(cmd, "");
//	get_last_node_arg(cmd->list_args)->type = type;
//	if (type == REDIRECT_INPUT || type == REDIRECT_OUTPUT)
//		len += 1;
//	else if (type == REDIRECT_OUTPUT_APPEND)
//		len += 2;
//	return (input + len);
//}

char	*create_arg(t_cmd *cmd, char *input)
{
	t_arg			*last_arg;
	int				len;

	len = 0;
	while (is_space(*input))
		input++;
	if (!is_cmd(input))
	{
		len = str_len_token(input, is_arg(input));
		create_node_arg(cmd, ft_substr(input, 0, len));
		last_arg = get_last_node_arg(cmd->list_args);
		last_arg->type = is_arg(last_arg->arg);
	}
//	else
//		// else ficou para comandos acima de VAR_EXPAND no caso os redirects e o BROKEN_QUOTES que definimos juntos.
//		input = handle_redirect(type, len, cmd, input);
	input = input + len;
	while (is_space(*input))
		input++;
	return (input);
}

char	*create_cmd(t_control *control, char *actual)
{
	int	len;
	t_cmd *node;

	len = 0;
	while (is_space(*actual))
		actual++;
	if (!*actual)
		return (actual);
	if (is_cmd(actual))
		create_node_cmd(control, (char *)"");
	else
	{
		len = str_len_token(actual, is_arg(actual));
		create_node_cmd(control, ft_substr(actual, 0, len));
		node = get_last_node_cmd(control->cmd);
		node->type = is_arg(node->cmd);
	}
	actual = actual + len;
	while (is_space(*actual))
		actual++;
	return (actual);
}

char	*handle_token(t_control *control, char *input)
{
	char			*actual;
	enum e_type_cmd	result_is_cmd;

	actual = input;
	while (*actual)
	{
		actual = create_cmd(control, actual);
		while (*actual)
		{
			result_is_cmd = is_cmd(actual);
			if (result_is_cmd)
			{
				get_last_node_cmd(control->cmd)->delimiter_type = result_is_cmd;
				if (result_is_cmd == PIP)
					actual++;
				break ;
			}
			else
				actual = create_arg(get_last_node_cmd(control->cmd), actual);
		}
	}
	return (actual);
}
