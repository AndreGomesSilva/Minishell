//
// Created by Alaide e Julio on 23/12/2023.
//

#include "../../include/minishell.h"

int is_variable(t_lst *node)
{
	if (node && node->token_name[0] == '$')
		return (1);
	return (0);
}

char *get_var(char *var, char **env)
{
	char *result;
	int i;
	int j;

	i = 0;
	result = NULL;
	while (env[i])
	{
		j = 0;
		while (var[j] && env[i][j] && var[j] == env[i][j])
		{
			if (env[i][j + 1] == '=' && env[i][j + 2])
				result = ft_strdup(&env[i][j + 2]);
			j++;
		}
		i++;
	}
	return (result);
}

void expand_var(t_lst *node, char **env)
{
	char *var;

	node->type = VAR;
	var = &node->token_name[1];
	node->value = get_var(var, env);
	if (!node->value)
		node->value = ft_strdup("");
}

void handle_var(t_control *control, char **env)
{
	t_lst *node;

	node = control->lst;
	while(node)
	{
		if (is_variable(node))
			expand_var(node, env);
		node = node->next;
	}
}

void handle_expander(t_control *control, char **env)
{
	handle_var(control, env);
}