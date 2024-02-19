/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:38:20 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/19 18:29:49angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

int	get_outfile(t_cmd *cmd, int pipe_fd)
{
	char	*outfile;
	int		fd;

	outfile = get_last_outfile(cmd);
	if (outfile)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			print_error(cmd, E_NO_FILE);
		return (fd);
	}
	if (cmd->next == NULL)
		return (STDOUT_FILENO);
	return (pipe_fd);
}

int	get_infile(t_cmd *cmd, int pipe_fd)
{
	t_arg	*ptr_arg;
	int		fd;

	ptr_arg = cmd->list_args;
	if (ptr_arg && cmd->type == REDIRECT_INPUT)
	{
		fd = open(ptr_arg->arg, O_RDONLY);
		return (fd);
	}
	while (ptr_arg)
	{
		if (ptr_arg->type == REDIRECT_INPUT && ptr_arg->next)
		{
			fd = open(ptr_arg->next->arg, O_RDONLY);
			return (fd);
		}
		ptr_arg = ptr_arg->next;
	}
	if (cmd->cmd_number == 1)
		return (STDIN_FILENO);
	return (pipe_fd);
}

void	close_fd(int in, int out)
{
	if (in != STDIN_FILENO)
		close(in);
	if (out != STDOUT_FILENO)
		close(out);
}

void	change_stdio(t_cmd *cmd, int in, int out)
{
	if (in != STDIN_FILENO)
	{
		cmd->infile = dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		cmd->outfile = dup2(out, STDOUT_FILENO);
		close(out);
	}
}



int	handle_io(t_cmd *cmd, int **pipe_fd, int index, int multi_cmd)
{
	if (multi_cmd)
	{
		if (cmd->cmd_number == 1)
		{
			cmd->infile = get_infile(cmd, 0);
			cmd->outfile = get_outfile(cmd, pipe_fd[index][1]);
		}
		else if (cmd->next == NULL)
		{
			cmd->infile = get_infile(cmd, pipe_fd[index - 1][0]);
			cmd->outfile = get_outfile(cmd, 1);
		}
		else
		{
			cmd->infile = get_infile(cmd, pipe_fd[index - 1][0]);
			cmd->outfile = get_outfile(cmd, pipe_fd[index][1]);
		}
	}
	else {
		cmd->infile = get_infile(cmd, 0);
		cmd->outfile = get_outfile(cmd, 1);
	}
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (FALSE);
	return (TRUE);
}
