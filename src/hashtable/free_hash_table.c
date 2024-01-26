//
// Created by angomes- on 1/24/24.
//

#include "../../include/minishell.h"

void free_hash_table(t_table *table)
{
	int	i;
	t_ht_item **items;
	t_ht_item *next_tem;

	i = 0;
	if (table)
	{
		items = table->items;
		if (items)
		{
			while (i < table->size)
			{
				if (table->items[i])
				{
					next_tem = items[i]->next;
					if (items[i]->value)
						free(items[i]->value);
					if (items[i]->key)
						free(items[i]->key);
					items[i]->next = NULL;
					items[i] = next_tem;
				}
				i++;
			}
			free(items);
		}
		free(table);
	}
}