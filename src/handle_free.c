/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:17:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/08 18:17:36 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ht_item *free_node(t_ht_item *node)
{
	t_ht_item	*next_node;

	next_node = node->next;
	if (node->value)
		free(node->value);
	if (node->key)
		free(node->key);
	free(node);
	return (next_node);
}

void free_hash_table(t_table *table)
{
	int			i;
	t_ht_item	**items;
	t_ht_item	*item;

	i = -1;
	if (table)
	{
		items = table->items;
		if (items)
		{
			while (i++, i < table->size)
			{
				item = table->items[i];
				while (item)
				{
					item = free_node(item);
				}
			}
			free(items);
			table->items = NULL;
		}
		free(table);
	}
}

void	free_arg(t_arg *list_args)
{
	t_arg	*temp_node;

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

void	free_control(t_control *control)
{
	if (control->env_table)
		free_hash_table(control->env_table);
	if (control->env)
		free_matrix(control->env);
	if (control->prompt)
		free(control->prompt);
	if (control->cmd)
		free_cmd(control);
	free(control);
}
