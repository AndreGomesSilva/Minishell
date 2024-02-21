/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:31:53 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/21 15:35:00ngomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_quote_eof(char *eof)
{
	int		i;
	int		j;
	int		quote;
	char	type_quote;

	i = 0;
	quote = 1;
	while (eof[i])
	{
		if (eof[i] == '"' || eof[i] == '\'')
		{
			type_quote = eof[i];
			j = i + 1;
			while (eof[j] != type_quote)
			{
				j++;
				if (!eof[j])
					return (BROKEN_QUOTES);
			}
			return (quote);
		}
		i++;
	}
	return (NORM);
}

char	*swap_string(char *str, char *sub_str)
{
	char	*result;

	result = NULL;
	if (str && sub_str)
	{
		result = ft_strjoin(str, sub_str);
		free(str);
		free(sub_str);
	}
	else if (sub_str)
		result = sub_str;
	else if (str)
		result = str;
	return (result);
}
char	*get_string_without_quotes(char *str, char *result, int i)
{
	char	type_quote;

	while (str && *str)
	{
		if (*str == '"' || *str == '\'')
		{
			result = swap_string(result, ft_substr(str - i, 0, i));
			type_quote = *str++;
			i = 0;
			while (str[i] && str[i] != type_quote)
				i++;
			result = swap_string(result, ft_substr(str, 0, i));
			str = &str[i + 1];
			i = 0;
		}
		else if (*str)
		{
			str++;
			i++;
		}
	}
	if (i > 0 && !*str)
		result = swap_string(result, ft_substr(str - i, 0, i));
	return (result);
}

char	*remove_quotes(char *str)
{
	char	*ptr_str;
	char	*result;
	int		i;

	i = 0;
	ptr_str = str;
	result = NULL;
	result = get_string_without_quotes(str, result, i);
	if (!result)
		result = ft_strdup(ptr_str);
	return (result);
}

void	handle_quotes_parsing(t_control *control)
{
	t_cmd	*ptr_cmd;
	char	*temp_cmd;
	t_arg	*ptr_arg;
	char	*temp_arg;

	ptr_cmd = control->cmd;
	while (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		temp_cmd = remove_quotes(ptr_cmd->cmd);
		free(ptr_cmd->cmd);
		ptr_cmd->cmd = temp_cmd;
		while (ptr_arg)
		{
			temp_arg = remove_quotes(ptr_arg->arg);
			free(ptr_arg->arg);
			ptr_arg->arg = temp_arg;
			ptr_arg = ptr_arg->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
}
