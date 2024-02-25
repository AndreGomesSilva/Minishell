/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:21:09 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/17 14:56:54by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_wait(int n_pipes)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	while (i < n_pipes + 1)
	{
		pid = waitpid(-1, &status, WUNTRACED);
		if (pid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (status);
}

void	single_execution_builtin(t_control *control)
{
	t_cmd	*ptr_cmd;
	int		old_stdin;
	int		old_stdout;

	ptr_cmd = control->cmd;
	if (handle_io(ptr_cmd, NULL, 0, FALSE))
	{
		if (ptr_cmd->error_type)
		{
			close_fd(control->cmd->infile, control->cmd->outfile);
			print_error(ptr_cmd, ptr_cmd->error_type);
		}
		if (ptr_cmd->infile == STDIN_FILENO
			&& ptr_cmd->outfile == STDOUT_FILENO)
			handle_builtin(ptr_cmd->cmd_and_args, control);
		else
		{
			old_stdin = dup(STDIN_FILENO);
			old_stdout = dup(STDOUT_FILENO);
			change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
			handle_builtin(ptr_cmd->cmd_and_args, control);
			change_stdio(old_stdin, old_stdout);
		};
	}
}

void	children_exec(t_control *control, t_cmd *cmd, int index, int n_pipes)
{
	handle_io(cmd, control->pipe_fd, index, TRUE);
	if (cmd->error_type || !cmd->cmd_and_args)
	{
		close_pipes(control->pipe_fd, n_pipes);
		close_fd(control->cmd->infile, cmd->outfile);
		print_error(cmd, cmd->error_type);
	}
	change_stdio(cmd->infile, cmd->outfile);
	if (cmd->cmd_and_args && handle_builtin(cmd->cmd_and_args, control))
	{
		close_pipes(control->pipe_fd, n_pipes);
		close_fd(control->cmd->infile, cmd->outfile);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_pipes(control->pipe_fd, n_pipes);
		free_control(control);
		exit(EXIT_SUCCESS);
	}
	close_pipes(control->pipe_fd, n_pipes);
	close_fd(control->cmd->infile, cmd->outfile);
	free_pipes(control->pipe_fd, n_pipes);
	execve(cmd->path_cmd, cmd->cmd_and_args, control->env);
	free_control(control);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	multi_execution(t_control *control, int n_pipes)
{
	t_cmd	*ptr_cmd;
	pid_t	pid;
	int		i;

	control->pipe_fd = create_pipes(n_pipes);
	if (!control->pipe_fd)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ptr_cmd = control->cmd;
	i = 0;
	while (ptr_cmd && i < n_pipes + 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			children_exec(control, ptr_cmd, i, n_pipes);
		ptr_cmd = ptr_cmd->next;
		i++;
	}
	close_pipes(control->pipe_fd, n_pipes);
	handle_wait(n_pipes);
	free_pipes(control->pipe_fd, n_pipes);
}

void	handle_execution(t_control *control)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = control->cmd;
	if (control->fatal_err)
	{
		printf("FATAL ERROR \n");
		control->fatal_err = 0;
		free_cmd(control);
		return ;
	}
	control->n_pipes = count_pipes(control->cmd);
	if (ptr_cmd && !control->n_pipes && ptr_cmd->cmd_and_args
		&& is_builtin(ptr_cmd->cmd_and_args[0]))
		single_execution_builtin(control);
	else
		multi_execution(control, control->n_pipes);
}
