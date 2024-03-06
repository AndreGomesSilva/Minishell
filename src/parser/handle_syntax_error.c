/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:15:17 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/06 15:13:27 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_cmd(t_cmd *cmd)
{
	if (cmd->cmd_and_args && cmd->cmd_and_args[0]
		&& cmd->cmd_and_args[0][0] == '\0')
		return (FALSE);
	if ((cmd->type >= REDIRECT_HERD && (cmd->cmd_and_args
				&& !(access(cmd->cmd_and_args[0], X_OK)))) || (cmd->path_cmd
			&& !access(cmd->path_cmd, X_OK)))
		return (TRUE);
	return (FALSE);
}

int	check_end_redirect(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	if (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		if ((ptr_cmd->type >= REDIRECT_HERD
				&& ptr_cmd->type <= REDIRECT_OUTPUT_APPEND) && (!ptr_arg
				|| (ptr_arg->type >= REDIRECT_HERD
					&& ptr_arg->type <= REDIRECT_OUTPUT_APPEND)))
			return (TRUE);
		while (ptr_arg)
		{
			if ((ptr_arg->type >= REDIRECT_HERD
					&& ptr_arg->type <= REDIRECT_OUTPUT_APPEND)
				&& (!ptr_arg->next || (ptr_arg->next->type >= REDIRECT_HERD
						&& ptr_arg->next->type <= REDIRECT_OUTPUT_APPEND)))
				return (TRUE);
			ptr_arg = ptr_arg->next;
		}
	}
	return (FALSE);
}

int	check_end_pipe(t_cmd *cmd)
{
	t_arg	*ptr_arg;

	ptr_arg = cmd->list_args;
	while (ptr_arg && ptr_arg->next && cmd->type_cmd)
		ptr_arg = ptr_arg->next;
	if (ptr_arg && (ptr_arg->type >= REDIRECT_HERD
			&& ptr_arg->type <= REDIRECT_OUTPUT_APPEND) && cmd->type_cmd
		&& !cmd->next && !ptr_arg->next)
		return (TRUE);
	if (cmd->type_cmd && !cmd->next)
		return (TRUE);
	return (FALSE);
}

int	handle_syntax_error_heredoc(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = cmd;
	if (ptr_cmd)
	{
		if (check_end_pipe(ptr_cmd) || check_end_redirect(ptr_cmd)
			|| ptr_cmd->cmd == NULL)
		{
			if (check_end_pipe(ptr_cmd))
				cmd->error_type = E_PIPE;
			if (check_end_redirect(ptr_cmd))
				cmd->error_type = E_REDIRECT;
			else if (ptr_cmd->cmd == NULL)
				cmd->error_type = E_REDIRECT;
			return (TRUE);
		}
	}
	return (FALSE);
}

int	handle_syntax_error(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = cmd;
	while (ptr_cmd)
	{
		if (check_end_pipe(ptr_cmd) || check_end_redirect(ptr_cmd)
			|| ptr_cmd->cmd == NULL)
		{
			if (check_end_pipe(ptr_cmd))
				cmd->error_type = E_PIPE;
			if (check_end_redirect(ptr_cmd))
				cmd->error_type = E_REDIRECT;
			else if (ptr_cmd->cmd == NULL)
				cmd->error_type = E_REDIRECT;
			return (TRUE);
		}
		ptr_cmd = ptr_cmd->next;
	}
	return (FALSE);
}
