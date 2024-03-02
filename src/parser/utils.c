/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:15:24 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/02 19:43:34by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	remove_dolar_arg(t_arg *arg)
// {

// }

// void	remove_dolar_cmd(t_cmd *cmd)
// {
// 	int i;
// 	char *temp;
// 	char *cmd_str;
// 	char *result;
// 	t_cmd *ptr_cmd;

// 	ptr_cmd = cmd;
// 	while (ptr_cmd)
// 	{
// 		cmd_str = ptr_cmd->cmd;
// 		while (cmd_str[i])
// 		{
// 			if (cmd_str[i] == '\"' || cmd_str[i] == '\'')
// 			{
// 				if (i > 0 && cmd_str[i - 1] == '$')
// 				{
// 					if (i - 1 == 0)
// 					{
// 						result = ft_substr(cmd_str, 1, i);
// 						free(cmd_str);
// 					}
// 					else
// 					{
// 						temp = ft_substr(ptr_cmd->cmd, 0, i - 2);
// 						result = swap_string(temp, ptr_cmd->cmd + i);
// 					}
// 					ptr_cmd->cmd = result;
// 				}
// 			}
// 			if (cmd_str[i])
// 				i++;
// 		}	
// 		ptr_cmd = ptr_cmd->next;
// 	}
// }

int	is_absolute_path(char *cmd)
{
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
