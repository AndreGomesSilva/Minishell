/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:21:09 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/16 15:27:50 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	int		count;

	ptr_cmd = cmd;
	count = 0;
	while (ptr_cmd)
	{
		if (ptr_cmd->delimiter_type == PIP)
			count++;
		ptr_cmd = ptr_cmd->next;
	}
	return (count);
}

void	single_execution_builtin(t_control *control)
{
	t_cmd	*ptr_cmd;
	int		pipe_fd[2];
	int		old_stdin;
	int		old_stdout;

	ptr_cmd = control->cmd;
	if (handle_io(ptr_cmd, pipe_fd))
	{
		old_stdin = dup(STDIN_FILENO);
		old_stdout = dup(STDOUT_FILENO);
		change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
		control->cmd_actual = control->cmd;
		handle_builtin(ptr_cmd->cmd_and_args, control);
		change_stdio(old_stdin, old_stdout);
		close_fd(ptr_cmd->infile, ptr_cmd->outfile);
	}
}

void	handle_execution(t_control *control)
{
	int		n_pipes;
	t_cmd	*ptr_cmd;

	ptr_cmd = control->cmd;
	if (control->fatal_err)
	{
		printf("FATAL ERROR \n");
		control->fatal_err = 0;
		free_cmd(control);
		return ;
	}
	n_pipes = count_pipes(control->cmd);
	if (ptr_cmd && !n_pipes && is_builtin(ptr_cmd->cmd))
		single_execution_builtin(control);
	// 	else
	// 			multi_execution(control);
}
