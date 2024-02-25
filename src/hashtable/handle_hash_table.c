/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hash_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:18 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/25 12:47:53 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(t_table *table)
{
	int			i;
	t_ht_item	*items;

	i = -1;
	if (table)
	{
		while (i++, i < table->size)
		{
			items = table->items[i];
			if (items)
			{
				if (items->key[0] == '?')
					continue ;
				printf("%s", items->key);
				printf("=%s\n", items->value);
				if (items->next)
				{
					printf("%s", items->next->key);
					printf("=%s\n", items->next->value);
				}
			}
		}
	}
}

void	remove_node_env(t_control *control, t_ht_item *previous_node,
		t_ht_item *node, int index)
{
	if (previous_node == node && !previous_node->next)
	{
		control->env_table->items[index] = previous_node->next;
		control->env_table->count--;
		free_node(node);
	}
	else
	{
		while (previous_node)
		{
			if (previous_node->next == node)
			{
				if (previous_node->next->next)
					previous_node->next = previous_node->next->next;
				else
					previous_node->next = NULL;
				control->env_table->count--;
				free_node(node);
				break ;
			}
			previous_node = previous_node->next;
		}
	}
}

void	remove_env(t_control *control, const char *key)
{
	t_ht_item	*node;
	t_ht_item	*previous_node;
	int			index;

	index = hash_function(key, control->env_table->size);
	node = get_var_node(control, (char *)key);
	previous_node = control->env_table->items[index];
	if (node)
		remove_node_env(control, previous_node, node, index);
}

void	update_env(t_control *control, const char *key, const char *value)
{
	int			index;
	t_ht_item	*temp_node;
	t_ht_item	*node;

	index = hash_function(key, control->env_table->size);
	node = get_var_node(control, (char *)key);
	if (node)
	{
		free(node->value);
		node->value = (char *)value;
	}
	else
	{
		node = create_hash_node(key, value);
		if (control->env_table->items[index] == NULL)
			control->env_table->items[index] = node;
		else
		{
			temp_node = control->env_table->items[index];
			while (temp_node->next)
				temp_node = temp_node->next;
			temp_node->next = node;
		}
		control->env_table->count++;
	}
	update_matrix_env(control);
}
