/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:26 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/08 16:22:33 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arg	*get_last_node_arg(t_arg *node)
{
	t_arg	*temp_node;

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

void	create_node_arg(t_cmd *cmd_node, const char *arg)
{
	t_arg	*node;
	t_arg	*temp_node;

	node = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (*arg)
		node->arg = (char *)arg;
	node->next = NULL;
	if (!cmd_node->list_args)
		cmd_node->list_args = node;
	else
	{
		temp_node = get_last_node_arg(cmd_node->list_args);
		temp_node->next = node;
	}
}
