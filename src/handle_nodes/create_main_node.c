//
// Created by angomes- on 12/1/23.
//

#include "../../include/minishell.h"

int	list_len(t_lst **lst)
{
	int		count;
	t_lst	*current;

	count = 0;
	current = *lst;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_lst	*last_node(t_lst *lst)
{
	t_lst	*temp_node;

	if (!lst)
		return (NULL);
	temp_node = lst;
	while (lst->next)
	{
		temp_node = lst->next;
		lst = temp_node;
	}
	return (temp_node);
}

void	create_main_node(t_lst **lst, char *cmd)
{
	t_lst	*node;
	t_lst	*temp_node;

	if (!lst)
		return ;
	node = ft_calloc(1, sizeof (t_lst));
	node->token_name = cmd;
	node->next = NULL;
	if (!*lst)
	{
		node->previous = NULL;
		*lst = node;
	}
	else
	{
		temp_node = last_node(*lst);
		temp_node->next = node;
		node->previous = temp_node;
	}
}