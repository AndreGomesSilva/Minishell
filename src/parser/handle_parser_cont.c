/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parser_cont.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:46:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/28 15:23:09 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	type_io_file(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	while (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		if (ptr_cmd->type > REDIRECT_HERD && ptr_arg && (ptr_arg->type == NORM
				|| ptr_arg->type == VAR_EXPAND))
		{
			ptr_arg->type = IOFILE;
			ptr_arg = ptr_arg->next;
		}
		while (ptr_arg)
		{
			if ((ptr_arg->type > REDIRECT_HERD && ptr_arg->type < IOFILE)
				&& ptr_arg->next && (ptr_arg->next->type == NORM
					|| ptr_arg->next->type == VAR_EXPAND))
				ptr_arg->next->type = IOFILE;
			ptr_arg = ptr_arg->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
}

int	count_args(t_cmd *cmd)
{
	int		count;
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	ptr_arg = ptr_cmd->list_args;
	count = 0;
	if (ptr_cmd && ptr_cmd->type < REDIRECT_HERD)
		count++;
	while (ptr_arg)
	{
		if (ptr_arg->type < REDIRECT_HERD)
			count++;
		ptr_arg = ptr_arg->next;
	}
	if (count < 0)
		return (0);
	return (count);
}
