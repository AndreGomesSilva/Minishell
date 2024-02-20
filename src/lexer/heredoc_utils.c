/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:07:24 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/20 09:49:55 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify_broken_quote(t_control *control)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = control->cmd;
	if (ptr_cmd && ptr_cmd->type == BROKEN_QUOTES)
		return (TRUE);
	while (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		while (ptr_arg)
		{
			if (ptr_arg->type == BROKEN_QUOTES)
				return (TRUE);
			ptr_arg = ptr_arg->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
	return (FALSE);
}

char	*get_next_eof(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*eof;

	eof = NULL;
	ptr_arg = cmd->list_args;
	while (ptr_arg)
	{
		if (ptr_arg->type == DOC)
		{
			ptr_arg->type = IOFILE;
			eof = (ptr_arg->arg);
			break ;
		}
		ptr_arg = ptr_arg->next;
	}
	return (eof);
}

int	find_heredoc_arg(t_cmd *cmd)
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
				return (FALSE);
			else if (arg->next->type <= VAR_EXPAND)
			{
				arg->next->type = DOC;
				result = TRUE;
			}
		}
		arg = arg->next;
	}
	return (result);
}

int	find_heredoc_cmd(t_cmd *cmd)
{
	int	result;

	result = 0;
	if (cmd->type == REDIRECT_HERD)
	{
		if (cmd->list_args == NULL || cmd->list_args->type > VAR_EXPAND)
			return (FALSE);
		else if (cmd->list_args->type <= VAR_EXPAND)
		{
			cmd->list_args->type = DOC;
			result = TRUE;
		}
	}
	result += find_heredoc_arg(cmd);
	return (result);
}
