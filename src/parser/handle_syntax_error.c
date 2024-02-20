/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:15:17 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/20 19:44:36 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_cmd(t_cmd *cmd)
{
	if (cmd->type >= REDIRECT_HERD || (cmd->path_cmd && (!access(cmd->path_cmd,
					X_OK))))
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
		if ((ptr_cmd->type >= REDIRECT_HERD && ptr_cmd->type <= REDIRECT_OUTPUT_APPEND) 
			&& !ptr_arg)
			return (TRUE);
		while (ptr_arg)
		{
			if ((ptr_arg->type >= REDIRECT_HERD && ptr_arg->type <= REDIRECT_OUTPUT_APPEND)
				&& !ptr_arg->next)
				return (TRUE);
			ptr_arg = ptr_arg->next;
		}
	}
	return (FALSE);
}

int	check_end_pipe(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = cmd;
	if (ptr_cmd->delimiter_type && !ptr_cmd->next)
		return (TRUE);
	else
		return (FALSE);
}

int	handle_syntax_error(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = cmd;
	while (ptr_cmd)
	{
		if (check_end_pipe(cmd) || check_end_redirect(cmd)
			|| ptr_cmd->cmd == NULL)
			return (TRUE);
		ptr_cmd = ptr_cmd->next;
	}
	return (FALSE);
}
