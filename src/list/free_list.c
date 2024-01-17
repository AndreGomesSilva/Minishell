//
// Created by angomes- on 12/6/23.
//

#include "../../include/minishell.h"

void	free_arg(t_arg *list_args)
{
	t_arg 	*temp_node;

	while (list_args)
	{
		temp_node = list_args->next;
		if (list_args->arg)
			free(list_args->arg);
		free(list_args);
		list_args = temp_node;
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
		if (node->cmd)
			free(node->cmd);
		if (node->cmd_and_args)
			free_matrix(node->cmd_and_args);
		if (node->path_cmd)
			free(node->path_cmd);
		if (node->list_args)
			free_arg(node->list_args);
		free(node);
		node = temp_node;
	}
	control->cmd = NULL;
}