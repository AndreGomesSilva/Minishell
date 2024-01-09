//
// Created by Alaide e Julio on 23/12/2023.
//

#include "../../include/minishell.h"

int is_variable(t_arg *node)
{
	if (node && node->arg[0] == '$')
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

void expand_var(t_arg *node, char **env)
{
	char *var;

	node->type = VAR_EXPAND;
	var = &node->arg[1];
	node->arg = get_var(var, env);
	if (!node->arg)
		node->arg = ft_strdup("");
}

void handle_var(t_cmd *cmd, char **env)
{
	t_arg *node;

	node = cmd->list_args;
	while(node)
	{
		if (is_variable(node))
			expand_var(node, env);
		node = node->next;
	}
}

void handle_expander(t_control *control, char **env)
{
	handle_var(control->cmd, env);
}