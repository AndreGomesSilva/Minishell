/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:24:18 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/01 20:50:50y angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	finish_execution(t_control *control, t_cmd *cmd, int old_in,
		int old_out)
{
	close_fd(cmd->infile, cmd->outfile);
	close_fd(old_in, old_out);
	close_pipes(control->pipe_fd, control->n_pipes);
	free_pipes(control->pipe_fd, control->n_pipes);
	free(control->pid);
}

int	handle_wait(t_control *control)
{
	int	status;
	int	pid;
	int	i;

	i = 0;
	pid = 0;
	while (pid != -1)
	{
		pid = waitpid(control->pid[i], &status, 0);
		if (WIFEXITED(status))
			status = (WEXITSTATUS(status));
		i++;
	}
	return (status);
}

static void	children_exec(t_control *control, t_cmd *cmd, int old_in,
		int old_out)
{
	int	status;

	status = 0;
	if (cmd->cmd_and_args && handle_builtin(cmd->cmd_and_args, control))
	{
		status = ft_atoi(get_var_env(control, "?"));
		finish_execution(control, cmd, old_in, old_out);
		free_control(control);
		change_stdio(old_in, old_out);
		exit(status);
	}
	finish_execution(control, cmd, old_in, old_out);
	execve(cmd->path_cmd, cmd->cmd_and_args, control->env);
	change_stdio(old_in, old_out);
	free_control(control);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	catch_error(t_control *control, t_cmd *ptr_cmd, int old_in, int old_out)
{
	int	status;

	status = 0;
	finish_execution(control, ptr_cmd, old_in, old_out);
	if ((ptr_cmd->type == REDIRECT_HERD && !ptr_cmd->cmd_and_args)
		|| (ptr_cmd->type == VAR_EXPAND && !ptr_cmd->cmd_and_args[0]) ||
		ptr_cmd->error_type == E_CTRL_D_HERE)
		exit(0);
	control->status_cmd = print_error(ptr_cmd);
	status = control->status_cmd;
	free_control(control);
	exit(status);
}

void	start_process(t_control *control, t_cmd *ptr_cmd, int i)
{
	int	old_out;
	int	old_in;

	control->in_execution = 1;
	control->pid[i] = fork();
	signal(SIGQUIT, ctrl_bar);
	old_in = dup(STDIN_FILENO);
	old_out = dup(STDOUT_FILENO);
	if (control->pid[i] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (control->pid[i] == 0)
	{
		handle_io(ptr_cmd, control->pipe_fd, i, TRUE);
		if (ptr_cmd->error_type || !ptr_cmd->cmd_and_args)
			catch_error(control, ptr_cmd, old_in, old_out);
		change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
		children_exec(control, ptr_cmd, old_in, old_out);
	}
	close(old_in);
	close(old_out);
}
