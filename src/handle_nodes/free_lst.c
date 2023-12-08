//
// Created by angomes- on 12/6/23.
//

#include "../../include/minishell.h"

void	free_lst(t_control *control)
{
	t_lst	*node;
	t_lst	*temp_node;
	t_lst	*lst;

	lst = control->lst;
	node = lst;
	while (node)
	{
		temp_node = node->next;
		if (node->token_name)
			free(node->token_name);
		if (node->args)
			free_matrix(node->args);
		free(node);
		node = temp_node;
	}
}
