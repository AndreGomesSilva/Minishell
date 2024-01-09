//
// Created by angomes- on 12/6/23.
//

#include "../../include/minishell.h"

void	free_args(t_cmd *cmd)
{
	t_arg	*node;
	t_arg 	*temp_node;

	node = cmd->list_args;
	while (node)
	{
		temp_node = node->next;
		if (node->arg)
			free(node->arg);
		free(node);
		node = temp_node;
	}
}

void	free_cmd(t_control *control)
{
	t_cmd	*node;
	t_cmd	*temp_node;

	node = control->cmd;
	while (node)
	{
		temp_node = node->next;
		if (node->cmd_and_args)
			free(node->cmd_and_args);
		if (node->list_args)
			free_args(node);
		if (node->path_cmd)
			free(node->path_cmd);
		free(node);
		node = temp_node;
	}
}
