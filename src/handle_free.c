//
// Created by angomes- on 2/2/24.
//

#include "../include/minishell.h"

void free_hash_table(t_table *table)
{
	int	i;
	t_ht_item **items;
	t_ht_item *next_tem;

	i = -1;
	if (table)
	{
		items = table->items;
		if (items)
		{
			while (i++, i < table->size)
				while (items[i])
				{
					next_tem = items[i]->next;
					if (items[i]->value)
						free(items[i]->value);
					if (items[i]->key)
						free(items[i]->key);
					items[i]->next = NULL;
					items[i] = next_tem;
				}
			free(items);
		}
		free(table);
	}
}

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
		if (node->cmd_and_args)
			free_matrix(node->cmd_and_args);
		if (node->path_cmd)
			free(node->path_cmd);
		if (node->list_args)
			free_arg(node->list_args);
		if (node->cmd)
			free(node->cmd);
		free(node);
		node = temp_node;
	}
	control->cmd = NULL;
}

void	general_free(t_control *control)
{
	free_cmd(control);
	free_hash_table(control->env_table);
	free(control);
}