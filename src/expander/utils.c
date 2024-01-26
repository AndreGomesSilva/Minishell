//
// Created by angomes on 13/01/24.
//

#include "../../include/minishell.h"

int is_variable(char *str)
{
	if (str[0] && str[1] && str[0] == '$' && (ft_isalpha(str[1]) || str[1] == '_'))
		return (1);
	return (0);
}

//char *get_var(const char *var, char **env)
//{
//	char *result;
//	int i;
//	int j;
//
//	i = 0;
//	result = NULL;
//	while (env[i])
//	{
//		j = 0;
//		while (var[j] && env[i][j] && var[j] == env[i][j])
//		{
//			if (env[i][j + 1] == '=' && env[i][j + 2])
//				result = ft_strdup(&env[i][j + 2]);
//			j++;
//		}
//		i++;
//	}
//	return (result);
//}