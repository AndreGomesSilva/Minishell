//
// Created by angomes- on 2/8/24.
//

#include "../../include/minishell.h"

void print_hash_table (t_table *table)
{
	int	i;
	t_ht_item *items;

	i = 0;
	if (table)
		while (i < table->size)
		{
			items = table->items[i];
			if (items)
			{
				printf("%s", items->key);
				printf("=%s\n", items->value);
				if (items->next)
				{
					printf("%s", items->next->key);
					printf("=%s\n", items->next->value);
				}
			}
			i++;
		}
}

void remove_env_var(t_control *control, char *key)
{
	t_ht_item *node;
	t_ht_item *previous_node;
	int		  index;

	index = hash_function(key, control->env_table->size);
	node = get_var_node(control, key);
	previous_node = control->env_table->items[index];
	if (previous_node == node)
	{
		if (previous_node->next)
		{
			control->env_table->items[index] = previous_node->next;
			free_node(node);
		}
	}
	else
		while(previous_node && previous_node->next)
		{
			if (previous_node->next == node)
			{
				previous_node->next = node->next;
				free_node(node);
				break;
			}
			previous_node = previous_node->next;
		}
}

void update_env_var(t_control *control, char *key, char *value)
{
	int index;
	t_ht_item *temp_node;
	t_ht_item *node;

	index = hash_function(key, control->env_table->size);
	node = get_var_node(control, key);
	if (node)
	{
		free(node->value);
		node->value	= value;
	}
	else
	{
		node = create_hash_node(key, value);
		if (control->env_table->items[index] == NULL)
			control->env_table->items[index] = node;
		else
		{
			temp_node = control->env_table->items[index];
			while(temp_node->next)
				temp_node = temp_node->next;
			temp_node->next = node;
		}
		control->env_table->count++;
	}
}
