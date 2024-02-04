//
// Created by angomes- on 2/2/24.
//

#include "../../include/minishell.h"

int	check_end_redirect(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	if (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		if (ptr_cmd->type >= REDIRECT_HERD && !ptr_arg)
			return (TRUE);
		while (ptr_arg)
		{
			if (ptr_arg->type >= REDIRECT_HERD && !ptr_arg->next)
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
	t_cmd *ptr_cmd;

	ptr_cmd = cmd;
	while (ptr_cmd)
	{
		if (check_end_pipe(cmd) || check_end_redirect(cmd))
			return (TRUE);
		ptr_cmd = ptr_cmd->next;
	}
	return (FALSE);
}