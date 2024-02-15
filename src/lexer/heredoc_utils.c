/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:07:24 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/15 18:32:03 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			ptr_arg->type = NORM;
			eof = (ptr_arg->arg);
			break ;
		}
		ptr_arg = ptr_arg->next;
	}
	return (eof);
}

void	infinit_prompt(t_control *control)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (input)
			free(input);
		else
			receive_signal_ctrl_d(control);
	}
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
