/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path_without_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:46:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/27 19:46:55 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_path_without_command(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;
	int		i;

	ptr_cmd = cmd;
	ptr_arg = ptr_cmd->list_args;
	i = 0;
	while (ptr_arg)
	{
		if (ptr_arg->type == NORM || ptr_arg->type == VAR_EXPAND)
			ptr_arg->type = PATH;
		ptr_arg = ptr_arg->next;
	}
}