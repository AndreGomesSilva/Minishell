/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:07:24 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/10 00:08:44 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_heredoc_arg(t_cmd *cmd)
{
	t_arg	*arg;
	int		result;

	arg = cmd->list_args;
	result = 0;
	while (arg)
	{
		if (arg->type == REDIRECT_HERD)
		{
			if (arg->next == NULL || arg->next->type > VAR_EXPAND)
			{
				handle_error(cmd, SYNTAX);
				return (FALSE);
			}
			else if (arg->next->type < VAR_EXPAND)
			{
				arg->next->type = DOC;
				result = TRUE;
			}
		}
		arg = arg->next;
	}
	return (result);
}

int	search_heredoc_cmd(t_cmd *cmd)
{
	int	result;

	result = 0;
	if (cmd->type == REDIRECT_HERD)
	{
		if (cmd->list_args == NULL || cmd->list_args->type > VAR_EXPAND)
		{
			handle_error(cmd, SYNTAX);
			return (FALSE);
		}
		else if (cmd->list_args->type <= VAR_EXPAND)
		{
			cmd->list_args->type = DOC;
			result = TRUE;
		}
	}
	result += search_heredoc_arg(cmd);
	return (result);
}
