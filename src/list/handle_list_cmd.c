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

t_cmd	*get_last_node_cmd(t_cmd *node)
{
	t_cmd	*temp_node;

	if (!node)
		return (NULL);
	temp_node = node;
	while (node->next)
	{
		temp_node = node->next;
		node = temp_node;
	}
	return (temp_node);
}

void	create_node_cmd(t_control *control, char *cmd)
{
	t_cmd	*node;
	t_cmd	*temp_node;

	node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (*cmd)
		node->cmd = cmd;
	node->next = NULL;
	if (!control->cmd)
	{
		node->prev = NULL;
		control->cmd = node;
	}
	else
	{
		temp_node = get_last_node_cmd(control->cmd);
		temp_node->next = node;
		node->prev = temp_node;
	}
}
