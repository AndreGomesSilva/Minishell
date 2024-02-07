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

char 	**get_matrix_env(t_control *control)
{
	char **env_matrix;
	t_ht_item *items;
	int	i;
	int j;

	i = -1;
	j = 0;
	env_matrix = NULL;
	if (control->env_table)
	{
		env_matrix = (char **) ft_calloc(control->env_table->count + 1, sizeof(char *));
		while (i++, i < control->env_table->size)
		{
			items = control->env_table->items[i];
			while (items)
			{
					env_matrix[j++]= ft_strdup(items->key);
					items = items->next;
			}
		}
	}
	return (env_matrix);
}

void print_sort_env(t_control *control)
{
	char **env;
	t_ht_item *item;
	int i;

	i = 0;
	env = get_matrix_env(control);
	matrix_quicksort(env, 0, control->env_table->count - 1);
	if (env)
	{
		while (env[i])
		{
			item = get_var_node(control, env[i]);
			if (item && !(item->key[0] == '_' && !item->key[1]))
				printf("declare -x %s=%s\n", item->key, item->value);
			i++;
		}
		free_matrix(env);
	}
}