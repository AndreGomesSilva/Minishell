//
// Created by angomes- on 1/26/24.
//

#include "../../include/minishell.h"

char	*get_var(t_control *control, const char *key)
{
	int index;
	char *result;
	t_ht_item *node;

	result = NULL;
	if (!control->env_table)
		return(result);	
	index = hash_function(key, control->env_table->size);
	node = control->env_table->items[index];
	while (node)
	{
		if (!ft_strncmp(key, node->key, ft_strlen(key)) && !ft_strncmp(node->key, key, ft_strlen(node->key)))
			result = node->value;
		node = node->next;
	}
	return (result);
}

t_ht_item *get_var_node(t_control *control, char *key)
{
	int			index;
	t_ht_item	*node;
	t_ht_item	*result;

	result = NULL;
	if (!control->env_table)
		return (result);
	index = hash_function(key, control->env_table->size);
	node = control->env_table->items[index];
	while (node)
	{
		if (!ft_strncmp(key, node->key, ft_strlen(key)) && !ft_strncmp(node->key, key, ft_strlen(node->key)))
			result = node;
		node = node->next;
	}
	return (result);
}