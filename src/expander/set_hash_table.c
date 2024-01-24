//
// Created by angomes- on 1/23/24.
//

#include "../../include/minishell.h"

int	len_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ft_pow(int base, int exponent)
{
	int result;
	int i;

	result = 1;
	i = 0;
	if (exponent == 0)
		return (result);
	while (i < exponent)
	{
		result *= base;
		i++;
	}
	return (result);
}

int	hash_function(char *str, int size)
{
	long int hash;
	int 	len;
	int 	 i;

	len = ft_strlen(str);
	hash = 0;
	i = 0;
	while (i < len)
	{
		hash += (long) ft_pow(131, len - (i + 1)) * str[i];
		hash = hash % size;
		i++;
	}
	return ((int)hash);
}

t_ht_item	*create_hash_node(char *key, char *value)
{
	t_ht_item *node;
	node = ft_calloc(1, sizeof(t_ht_item));
	node->key = key;
	node->value = value;
	node->next = NULL;

	return (node);
}

void add_node_to_table(t_table *table, char *key, char *value)
{
	int index;
	t_ht_item *temp_node;
	t_ht_item *node;

	index = hash_function(key, table->size);
	node = create_hash_node(key, value);
	if (table->items[index] == NULL)
		table->items[index] = node;
	else
	{
		temp_node = table->items[index];
		while(temp_node)
			temp_node = temp_node->next;
		temp_node = node;
	}
}

t_ht_item *init_hash_table(t_control *control, char **env, t_table *table)
{
	int index;

	index = ;

}

t_table *init_table(t_control *control, char **env)
{
	t_table *table;
	int		arr_size;

	arr_size = len_env(env) * 3;
	table = malloc(sizeof(t_table));
	table->count = 0;
	table->size = arr_size;
	table->items = ft_calloc(table->size, sizeof(t_ht_item *));
	return (table);
}

int copy_env(t_control *control, char **env)
{
	t_table *table;

	table = init_table(control, env);
//	new_hashtable(control,env,  table);
}