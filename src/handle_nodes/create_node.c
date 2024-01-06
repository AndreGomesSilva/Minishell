//
// Created by angomes- on 12/1/23.
//

#include "../../include/minishell.h"

int	list_len(t_cmd *cmd)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_cmd	*get_last_node(t_cmd *cmd)
{
	t_cmd	*temp_node;

	if (!cmd)
		return (NULL);
	temp_node = cmd;
	while (cmd->next)
	{
		temp_node = cmd->next;
		cmd = temp_node;
	}
	return (temp_node);
}

void	create_node(t_control *control, char *cmd)
{
	t_cmd	*node;
	t_cmd	*temp_node;

	node = (t_cmd *)ft_calloc(1, sizeof (t_cmd));
	node->cmd = cmd;
	node->next = NULL;
	if (!control->cmd)
	{
		node->previous = NULL;
		control-> = node;
	}
	else
	{
		temp_node = last_node(control->cmd);
		temp_node->next = node;
		node->previous = temp_node;
	}
}
