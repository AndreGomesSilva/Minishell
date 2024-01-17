//
// Created by Alaide e Julio on 23/12/2023.
//

#include "../../include/minishell.h"

void expand_var(t_arg *node, char **env)
{
	char *var;

	node->type = VAR_EXPAND;
	var = &node->arg[1];
	node->arg = get_var(var, env);
	if (!node->arg)
		node->arg = ft_strdup("");
}

void handle_node_var(t_cmd *cmd, char **env)
{
	t_arg *node;

	node = cmd->list_args;
	while(node)
	{
		if (is_variable(node->arg))
			expand_var(node, env);
		node = node->next;
	}
}

void search_quote_var(t_control *control, t_arg *arg_node)
{
	char *result;
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (arg_node->arg[i])
	{
		if(is_variable(&arg_node->arg[i]))
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		result = get_var_double_quote(control, arg_node);
		free(arg_node->arg);
		arg_node->arg = result;
	}
}

void handle_expander(t_control *control, char **env)
{
	t_cmd *cmd_node_temp;
	t_cmd *cmd_node;
	t_arg *arg_node_temp;
	t_arg *arg_node;

	cmd_node = control->cmd;
	while (cmd_node)
	{
		arg_node = cmd_node->list_args;
		cmd_node_temp = cmd_node->next;
		while (arg_node)
		{
			arg_node_temp = arg_node->next;
			if (arg_node->type == VAR_EXPAND)
				handle_node_var(control->cmd, env);
			else if (arg_node->type == DOUBLE_QUOTE)
				search_quote_var(control, arg_node);
			arg_node = arg_node_temp;
		}
		cmd_node = cmd_node_temp;
	}
}