/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:38:20 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/17 16:46:38 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	close_fd(int in, int out)
{
	if (in != 0)
		close(in);
	if (out != 1)
		close(out);
}

int	handle_io(t_cmd *cmd, int *pipe_fd)
{
	cmd->infile = get_infile(cmd, pipe_fd[0]);
	cmd->outfile = get_outfile(cmd, pipe_fd[1]);
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (FALSE);
	return (TRUE);
}
