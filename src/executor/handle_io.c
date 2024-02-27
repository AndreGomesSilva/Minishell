/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:37:50 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/27 13:37:52 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_outfile(t_cmd *cmd, int pipe_fd)
{
	char	*outfile;
	int		fd;
	int		type;

	fd = STDOUT_FILENO;
	type = 0;
	outfile = get_last_outfile(cmd, &type);
	if (outfile)
	{
		if (type == 0)
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (type == 1)
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		return (fd);
	}
	if (cmd->next == NULL)
		return (fd);
	return (pipe_fd);
}

int	get_infile(t_cmd *cmd, int pipe_fd)
{
	int		fd;
	char	*infile;

	fd = STDIN_FILENO;
	infile = get_last_infile(cmd);
	if (infile)
	{
		fd = open(infile, O_RDONLY);
		return (fd);
	}
	if (cmd->cmd_number == 1)
		return (fd);
	return (pipe_fd);
}

void	close_fd(int in, int out)
{
	if (in != STDIN_FILENO)
		close(in);
	if (out != STDOUT_FILENO)
		close(out);
}

void	change_stdio(int in, int out)
{
	if (in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

int	handle_io(t_cmd *cmd, int **pipe_fd, int index, int multi_cmd)
{
	if (multi_cmd)
	{
		if (cmd->cmd_number == 1)
		{
			close(pipe_fd[index][0]);
			cmd->infile = get_infile(cmd, 0);
			cmd->outfile = get_outfile(cmd, pipe_fd[index][1]);
		}
		else if (cmd->next == NULL)
		{
			close (pipe_fd[index - 1][1]);
			close (pipe_fd[index][1]);
			close (pipe_fd[index][0]);
			cmd->infile = get_infile(cmd, pipe_fd[index - 1][0]);
			cmd->outfile = get_outfile(cmd, 1);
		}
		else
		{
			close (pipe_fd[index - 1][1]);
			close (pipe_fd[index][0]);
			cmd->infile = get_infile(cmd, pipe_fd[index - 1][0]);
			cmd->outfile = get_outfile(cmd, pipe_fd[index][1]);
		}
	}
	else
	{
		cmd->infile = get_infile(cmd, 0);
		cmd->outfile = get_outfile(cmd, 1);
	}
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (FALSE);
	return (TRUE);
}
