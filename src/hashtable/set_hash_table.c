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
			while (i < table->size) {
				if (items[i])
				{
					next_tem = items[i]->next;
					printf("\nindex : %d", i);
					printf("\nkey = %s", items[i]->key);
					printf("   value = %s ", items[i]->value);
					if (items[i]->next)
					{
						printf("\n ----->   key = %s", items[i]->next->key);
						printf("\n ----->   next value = %s", items[i]->next->value);
					}
				}
				i++;
			}
	}
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
	node = (t_ht_item *)ft_calloc(1, sizeof(t_ht_item));
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

	arr_size = len_env(env) * 5;
	table = (t_table *)malloc(sizeof(t_table));
	table->count = 0;
	table->size = arr_size;
	table->items = (t_ht_item **)ft_calloc(table->size, sizeof(t_ht_item *));
	control->env_table = table;
	return (table);
}

int strlen_var_name(char *str)
{
	int i;
	i = 0;

	while(str[i] && str[i] != '=')
		i++;
	return (i);
}

void	copy_env(t_control *control, char **env)
{
	char *key;
	char *value;
	int   i;

	i = 0;
	while(env[i])
	{
		key = ft_substr(env[i], 0, strlen_var_name(env[i]));
		value = strdup(getenv(key));
		add_item_to_table(control->env_table, key, value);
		i++;
	} 
}


