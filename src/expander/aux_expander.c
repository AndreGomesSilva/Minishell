/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:44:21 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/27 13:43:48 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_join_var(int *i, char *str, char *var, char *end)
{
	char	*result;
	char	*temp;
	int		len;

	result = NULL;
	temp = ft_strjoin(str, var);
	len = ft_strlen(temp);
	*i = len;
	result = ft_strjoin(temp, end);
	free(str);
	free(var);
	free(temp);
	return (result);
}

char	*get_expander_var(t_control *control, char *str, int *i, int *j)
{
	char	*var;
	char	*key;
	char	*temp;

	if (is_exit_variable(&str[*i]))
		*j = *j + 1;
	else
	{
		while (ft_isalnum(str[*i + 1 + *j]) || str[*i + 1 + *j] == '_')
			*j = *j + 1;
	}
	key = ft_substr(&str[*i + 1], 0, *j);
	temp = get_var_env(control, key);
	if (temp)
		var = ft_strdup(temp);
	else
		var = ft_strdup("");
	free(key);
	return (var);
}

char	*expand_var(t_control *control, int *i, char *str)
{
	char	*new_str;
	char	*var;
	int		j;

	if (str[*i] && (is_variable(&str[*i]) || is_exit_variable(&str[*i])))
	{
		j = 0;
		var = get_expander_var(control, str, i, &j);
		new_str = ft_join_var(i, ft_substr(str, 0, *i), var, &str[*i + 1 + j]);
		if (new_str != NULL)
		{
			free(str);
			str = NULL;
		}
		str = new_str;
	}
	else if (str[*i])
		*i = *i + 1;
	return (str);
}
