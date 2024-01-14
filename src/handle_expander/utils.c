//
// Created by angomes on 13/01/24.
//

#include "../../include/minishell.h"

int is_variable(char *str)
{
	if (str && str[0] == '$' && (ft_isalpha(str[1]) || str[1] == '_'))
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

char *ft_join_var(t_control *control, char *str, char *var, char *end)
{
	char *result;
	char *temp;
	char *expand_var;

	result = NULL;
	expand_var = get_var(var, control->env);
	if (expand_var)
	{
		temp = ft_strjoin(str, expand_var);
		result = ft_strjoin(temp, end);
		free(str);
		free(expand_var);
		free(var);
		free(temp);
	}
	else
	{
		result = ft_strjoin(str, end);
		free(str);
		free(var);
	}
	return (result);
}

char *get_var_double_quote(t_control *control, t_arg *double_quote_arg)
{
	char	*str;
	char    *var;
	int 	i;
	int 	j;

	i = 0;
	str = double_quote_arg->arg;
	while(str[i])
	{
		if(is_variable(&str[i]))
		{
			j = 0;
			while (ft_isalpha(str[i + 1 + j]) || str[i + 1 + j] == '_')
				j++;
			var = ft_substr(&str[i + 1], 0, j);
			str = ft_join_var(control, ft_substr(str, 0, i), var, &str[i + 1 + j]);
			i = 0;
		}
		i++;
	}
	return (str);
}

