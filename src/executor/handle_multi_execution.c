/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:24:18 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/05 23:59:01 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_and_free(t_control *control, t_cmd *cmd, int old_in,
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
	pid = waitpid(control->pid[i], &status, 0);
	while (pid != -1)
	{
		if (WIFEXITED(status))
			status = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
				status = 128 + WTERMSIG(status);
		}
		i++;
		pid = waitpid(control->pid[i], &status, 0);
	}
	if (status == 131)
		printf("Quit (core dumped)\n");
	return (status);
}

static void	children_exec(t_control *control, t_cmd *cmd, int old_in,
		int old_out)
{
	int	status;

	status = 0;
	control->exit_fd[0] = old_in;
	control->exit_fd[1] = old_out;
	if (cmd->cmd_and_args && handle_builtin(cmd->cmd_and_args, control))
	{
		status = ft_atoi(get_var_env(control, "?"));
		close_and_free(control, cmd, old_in, old_out);
		free_control(control);
		change_stdio(old_in, old_out);
		exit(status);
	}
	close_and_free(control, cmd, old_in, old_out);
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
	close_and_free(control, ptr_cmd, old_in, old_out);
	if ((ptr_cmd->type == REDIRECT_HERD && !ptr_cmd->cmd_and_args)
		|| (ptr_cmd->type == VAR_EXPAND && ptr_cmd->cmd_and_args
			&& ptr_cmd->cmd_and_args[0] && ptr_cmd->cmd_and_args[0][0] == '\0')
		|| ptr_cmd->error_type == E_CTRL_D_HERE)
	{
		free_control(control);
		exit(0);
	}
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
