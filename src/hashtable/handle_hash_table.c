/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hash_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:18 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 01:25:28 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_hash_table(t_table *table)
{
	int			i;
	t_ht_item	*items;

	i = 0;
	if (table)
	{
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
}

void	remove_env_var(t_control *control, const char *key)
{
	t_ht_item	*node;
	t_ht_item	*previous_node;
	int			index;

	index = hash_function(key, control->env_table->size);
	node = get_var_node(control, (char *)key);
	previous_node = control->env_table->items[index];
	if (previous_node == node && previous_node->next)
	{
		control->env_table->items[index] = previous_node->next;
		free_node(node);
	}
	else
	{
		while (previous_node && previous_node->next)
		{
			if (previous_node->next == node)
			{
				previous_node->next = free_node(node);
				break ;
			}
			previous_node = previous_node->next;
		}
	}
}

void	update_env_var(t_control *control, const char *key, const char *value)
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
}
