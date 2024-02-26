/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hash_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:18 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/26 16:24:50 by r-afonso         ###   ########.fr       */
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
				if (items->type_print == FALSE)
					printf("=%s", items->value);
				printf("\n");
				if (items->next)
				{
					printf("%s", items->next->key);
					if (items->type_print == FALSE)
						printf("=%s", items->next->value);
					printf("\n");
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

void	create_new_env(int index, t_ht_item *node, int type_print, t_control *control,
		const char *key, const char *value)
{
	t_ht_item	*temp_node;

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
	if (type_print)
		node->type_print = type_print;
	control->env_table->count++;
	if (type_print)
		node->type_print = type_print;
}

void	update_env(t_control *control, const char *key, const char *value,
		int type_print)
{
	int			index;
	t_ht_item	*node;

	index = hash_function(key, control->env_table->size);
	node = get_var_node(control, (char *)key);
	if (node)
	{
		free(node->key);
		node->key = (char *)key;
		if (type_print == FALSE)
		{
			free(node->value);
			node->value = (char *)value;
			node->type_print = FALSE;
		}
		else
			free((char *)value);
	}
	else
		create_new_env(index, node, type_print, control, (char *)key, (char *)value);
	update_matrix_env(control);
}
