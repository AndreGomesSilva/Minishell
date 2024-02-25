/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:59:19 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/25 12:47:00 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_env_matrix(char **env_matrix, t_ht_item *items, int *j)
{
	char	*temp;

	while (items)
	{
		temp = ft_strjoin(items->key, "=");
		env_matrix[*j] = ft_strjoin(temp, items->value);
		free(temp);
		*j = *j + 1;
		while (items->next)
		{
			items = items->next;
			temp = ft_strjoin(items->key, "=");
			env_matrix[*j] = ft_strjoin(temp, items->value);
			free(temp);
			*j = *j + 1;
		}
		items = items->next;
	}
}

void	update_matrix_env(t_control *control)
{
	t_ht_item	*items;
	char		**env_matrix;
	int			j;
	int			i;

	
	i = -1;
	j = 0;
	env_matrix = NULL;
	if (control->env)
		free_matrix(control->env);
	env_matrix = (char **)ft_calloc(control->env_table->count + 1,
			sizeof(char *));
	while (++i < control->env_table->size)
	{
		items = control->env_table->items[i];
		if (items)
			create_env_matrix(env_matrix, items, &j);
	}
	control->env = env_matrix;
}
