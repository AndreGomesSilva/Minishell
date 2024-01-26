#include "../../include/minishell.h"

char *ft_join_var(char *str, char *var, char *end)
{
	char *result;
	char *temp;
	char *expand_var;

	result = NULL;
	expand_var = strdup(getenv(var));
	if (expand_var)
	{
		temp = ft_strjoin(str, expand_var);
		result = ft_strjoin(temp, end);
		free(str);
		free(expand_var);
		free(var);
		free(temp);
	}
	else
	{
		result = ft_strjoin(str, end);
		free(str);
		free(var);
	}
	return (result);
}

char *get_var_in_node(char *str)
{
	char    *var;
	int 	i;
	int 	j;

	i = 0;
	while(str[i])
	{
		if(is_variable(&str[i]))
		{
			j = 0;
			while (ft_isalpha(str[i + 1 + j]) || str[i + 1 + j] == '_')
				j++;
			var = ft_substr(&str[i + 1], 0, j);
			str = ft_join_var(ft_substr(str, 0, i), var, &str[i + 1 + j]);
			i = 0;
		}
		i++;
	}
	return (str);
}

void search_var_in_arg(t_cmd *node) {
	t_arg *temp_arg_node;
	t_arg *arg_node;

	arg_node = node->list_args;
	while (arg_node)
	{
		temp_arg_node = arg_node->next;
		if (arg_node->type == VAR_EXPAND)
			arg_node->arg = get_var_in_node(arg_node->arg);
		arg_node = temp_arg_node;
	}
}

void handle_expander(t_control *control)
{
	t_cmd *cmd_node_temp;
	t_cmd *cmd_node;

	cmd_node = control->cmd;
	while (cmd_node)
	{
		cmd_node_temp = cmd_node->next;
		if (cmd_node->type == VAR_EXPAND)
			cmd_node->cmd = get_var_in_node(cmd_node->cmd);
		search_var_in_arg(cmd_node);
		cmd_node = cmd_node_temp;
	}
}