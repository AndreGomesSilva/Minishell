/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:13:27 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/05 22:49:30 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_in_fds(t_cmd *cmd, int in)
{
	if (cmd && cmd->error_type == E_NO_ERROR)
	{
		if (cmd->redirec_in_file)
			cmd->infile = open(cmd->redirec_in_file, O_RDONLY);
		else
		{
			if (cmd->cmd_number == 1)
				cmd->infile = STDIN_FILENO;
			else
				cmd->infile = in;
		}
	}
	else
		cmd->infile = STDIN_FILENO;
}

void	set_out_fds(t_cmd *cmd, int out, int *type)
{
	if (cmd && cmd->error_type == E_NO_ERROR)
	{
		if (cmd->redirec_out_file)
		{
			if (*type == 0)
				cmd->outfile = open(cmd->redirec_out_file,
						O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				cmd->outfile = open(cmd->redirec_out_file,
						O_WRONLY | O_CREAT | O_APPEND, 0666);
		}
		else
		{
			if (cmd->next == NULL)
				cmd->outfile = STDOUT_FILENO;
			else
				cmd->outfile = out;
		}
	}
	else
		cmd->outfile = STDOUT_FILENO;
}
