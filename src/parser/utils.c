/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:23:54 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/06 18:24:54 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*remove_dolar(char *str, int i)
{
	char	*tail;
	char	*temp;
	char	*result;

	temp = ft_substr(str, 0, i - 1);
	tail = ft_substr(str, i, ft_strlen(str));
	result = swap_string(temp, tail);
	free(str);
	return (result);
}

static char	*find_dolar(char *str)
{
	int		i;
	char	*result;
	char	quote;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			if (i > 0 && str[i - 1] == '$')
			{
				result = remove_dolar(str, i);
				str = result;
			}
			else
				i++;
			while (str[i] && str[i] != quote)
				i++;
		}
		if (str[i])
			i++;
	}
	return (result);
}

void	remove_dolar_follow_quotes(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	char	*new_str;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	while (ptr_cmd)
	{
		new_str = find_dolar(ptr_cmd->cmd);
		if (new_str)
			ptr_cmd->cmd = new_str;
		ptr_arg = ptr_cmd->list_args;
		while (ptr_arg)
		{
			new_str = find_dolar(ptr_arg->arg);
			if (new_str)
				ptr_arg->arg = new_str;
			ptr_arg = ptr_arg->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
}

int	is_a_directory(char *cmd)
{
	if(*cmd == '/')
		return (TRUE);
	while (cmd && *cmd && cmd++)
		if (*cmd == '/')
			return (TRUE);
	return (FALSE);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!str_compare(cmd, "echo"))
		return (B_ECHO);
	else if (!str_compare(cmd, "cd"))
		return (B_CD);
	else if (!str_compare(cmd, "pwd"))
		return (B_PWD);
	else if (!str_compare(cmd, "env"))
		return (B_ENV);
	else if (!str_compare(cmd, "export"))
		return (B_EXPORT);
	else if (!str_compare(cmd, "unset"))
		return (B_UNSET);
	else if (!str_compare(cmd, "exit"))
		return (B_EXIT);
	return (B_NOBT);
}
