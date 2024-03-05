/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:37:50 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/04 23:52:17 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_fds(t_cmd *cmd, int in, int out, int *type)
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
		if (cmd->redirec_out_file)
		{
			if (type == 0)
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
	{
		cmd->infile = STDIN_FILENO;
		cmd->outfile = STDOUT_FILENO;
	}
}

void	get_file_arg(t_cmd *cmd, t_arg *arg, int *type)
{
	if (cmd->error_type == E_NO_ERROR && (arg->type == REDIRECT_INPUT || arg->type == REDIRECT_HERD))
		cmd->redirec_in_file = get_infile_arg(cmd, arg);
	else if (cmd->error_type == E_NO_ERROR && (arg->type == REDIRECT_OUTPUT
		|| arg->type == REDIRECT_OUTPUT_APPEND))
		cmd->redirec_out_file = get_outfile_arg(cmd, type, arg);
}

void	get_file_cmd(t_cmd *cmd, int *type)
{
	if (cmd->error_type == E_NO_ERROR && (cmd->type == REDIRECT_INPUT || cmd->type == REDIRECT_HERD))
		cmd->redirec_in_file = get_infile_cmd(cmd);
	else if (cmd->error_type == E_NO_ERROR && (cmd->type == REDIRECT_OUTPUT
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
	set_fds(cmd, in, out, &type);
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
