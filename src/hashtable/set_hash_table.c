/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hash_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:36 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 01:23:08 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hash_function(const char *str, int size)
{
	long int	hash;
	int			len;
	int			i;

	len = (int)ft_strlen(str);
	hash = 0;
	i = 0;
	while (i < len)
	{
		hash += (long)ft_pow(131, len - (i + 1)) * str[i];
		hash = hash % size;
		i++;
	}
	return ((int)hash);
}

t_ht_item	*create_hash_node(const char *key, const char *value)
{
	t_ht_item	*node;

	node = (t_ht_item *)ft_calloc(1, sizeof(t_ht_item));
	node->key = (char *)key;
	node->value = (char *)value;
	node->next = NULL;
	return (node);
}

t_table	*init_table(char **env)
{
	t_table	*table;
	int		arr_size;

	arr_size = len_env(env) * 3;
	table = (t_table *)malloc(sizeof(t_table));
	table->count = 0;
	table->size = arr_size;
	table->items = (t_ht_item **)ft_calloc(table->size, sizeof(t_ht_item *));
	return (table);
}

void	copy_env(t_control *control, char **env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		key = ft_substr(env[i], 0, strlen_var_name(env[i]));
		value = ft_strdup(getenv(key));
		update_env_var(control, key, value);
		i++;
	}
}
