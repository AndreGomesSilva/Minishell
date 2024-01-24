//
// Created by angomes- on 1/23/24.
//

#include "../../include/minishell.h"

void print_hash_table (t_table *table)
{

	int	i;
	t_ht_item **items;
	t_ht_item *next_tem;

	i = 0;
	if (table) {
		items = table->items;
		if (items) {
			while (items[i]) {
				next_tem = items[i]->next;
				printf("\nindex : %d", i);
				if (items[i]->value)
					printf("\nkey = %s", items[i]->key);
				if (items[i]->key)
				{
					printf("\nvalue = %s \n", items[i]->value);
					if (items[i]->next)
						printf("\n next value = %s \n", items[i]->next->value);
				}
				items[i]->next = NULL;
				items[i] = next_tem;
				i++;
			}
		}
	}
}

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

void add_item_to_table(t_table *table, char *key, char *value)
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
		while(temp_node->next)
			temp_node = temp_node->next;
		temp_node->next = node;
	}
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
	control->cmd = NULL;
}

int copy_env(t_control *control, char **env)
{
	t_table *table;
	char  *key = ft_strdup("hello");
	char  *value = ft_strdup("world");
	char  *key2 = ft_strdup("hello");
	char  *value2 = ft_strdup("teste");
	table = init_table(control, env);
	add_item_to_table(table, key, value);
	add_item_to_table(table, key2, value2);
	print_hash_table(table);
	free_hash_table(table);
	printf("\n FINISH \n");
	return (TRUE);
}