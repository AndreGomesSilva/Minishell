/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:37:50 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/05 22:20:29 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_file_arg(t_cmd *cmd, t_arg *arg, int *type)
{
	if (cmd->error_type <= E_CMD_NO_FOUND && (arg->type == REDIRECT_INPUT
			|| arg->type == REDIRECT_HERD))
		cmd->redirec_in_file = get_infile_arg(cmd, arg);
	else if (cmd->error_type <= E_CMD_NO_FOUND && (arg->type == REDIRECT_OUTPUT
			|| arg->type == REDIRECT_OUTPUT_APPEND))
		cmd->redirec_out_file = get_outfile_arg(cmd, type, arg);
}

void	get_file_cmd(t_cmd *cmd, int *type)
{
	if (cmd->error_type <= E_CMD_NO_FOUND && (cmd->type == REDIRECT_INPUT
			|| cmd->type == REDIRECT_HERD))
		cmd->redirec_in_file = get_infile_cmd(cmd);
	else if (cmd->error_type <= E_CMD_NO_FOUND && (cmd->type == REDIRECT_OUTPUT
			|| cmd->type == REDIRECT_OUTPUT_APPEND))
		cmd->redirec_out_file = get_outfile_cmd(cmd, type);
}

void	get_fds(t_cmd *cmd, int in, int out)
{
	t_arg	*ptr_arg;
	int		type;

	ptr_arg = cmd->list_args;
	if (cmd)
		get_file_cmd(cmd, &type);
	while (ptr_arg)
	{
		get_file_arg(cmd, ptr_arg, &type);
		ptr_arg = ptr_arg->next;
	}
	set_in_fds(cmd, in);
	set_out_fds(cmd, out, &type);
}

void	handle_io(t_cmd *cmd, int **pipe_fd, int index, int multi_cmd)
{
	if (multi_cmd)
	{
		if (cmd->cmd_number == 1)
			get_fds(cmd, 0, pipe_fd[index][1]);
		else if (cmd->next == NULL)
			get_fds(cmd, pipe_fd[index - 1][0], 1);
		else
			get_fds(cmd, pipe_fd[index - 1][0], pipe_fd[index][1]);
	}
	else
		get_fds(cmd, 0, 1);
	if (cmd->infile == -1 || cmd->outfile == -1)
		cmd->error_type = E_NO_FILE;
}
