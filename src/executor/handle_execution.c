/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:40:48 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/27 13:41:39 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_wait(t_control *control, int n_pipes)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	while (i < n_pipes + 1)
	{
		pid = waitpid(control->pid[i], &status, 0);
		if (pid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status));
		i++;
	}
	return (status);
}

void	single_execution_builtin(t_control *control)
{
	t_cmd	*ptr_cmd;
	int		old_stdin;
	int		old_stdout;
	int		cmd_is_builtin;

	ptr_cmd = control->cmd;
	handle_io(ptr_cmd, NULL, 0, FALSE);
	if (ptr_cmd->error_type)
	{
		close_fd(control->cmd->infile, control->cmd->outfile);
		control->status_cmd = print_error(ptr_cmd, ptr_cmd->error_type);
	}
	if (ptr_cmd->infile == STDIN_FILENO && ptr_cmd->outfile == STDOUT_FILENO)
		cmd_is_builtin = handle_builtin(ptr_cmd->cmd_and_args, control);
	else
	{
		old_stdin = dup(STDIN_FILENO);
		old_stdout = dup(STDOUT_FILENO);
		change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
		cmd_is_builtin = handle_builtin(ptr_cmd->cmd_and_args, control);
		change_stdio(old_stdin, old_stdout);
	}
	if (!cmd_is_builtin)
		update_env(control, ft_strdup("?"), ft_itoa(control->status_cmd),
			FALSE);
}

void	children_exec(t_control *control, t_cmd *cmd, int index, int n_pipes)
{
	int	status;

	status = 0;
	handle_io(cmd, control->pipe_fd, index, TRUE);
	dprintf(2, " 1: exit value: %d\n", status);
	if (cmd->error_type || !cmd->cmd_and_args)
	{
		close_pipes(control->pipe_fd, n_pipes);
		close_fd(control->cmd->infile, cmd->outfile);
		if (cmd->type == REDIRECT_HERD)
			exit(0);
		control->status_cmd = print_error(cmd, cmd->error_type);
		status = control->status_cmd;
		free_control(control);
		exit(status);
	}
	change_stdio(cmd->infile, cmd->outfile);
	if (cmd->cmd_and_args && handle_builtin(cmd->cmd_and_args, control))
	{
		close_pipes(control->pipe_fd, n_pipes);
		close_fd(control->cmd->infile, cmd->outfile);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_pipes(control->pipe_fd, n_pipes);
		status = control->status_cmd;
		dprintf(2, " 3: exit value: %d\n", status);
		free_control(control);
		exit(status);
	}
	close_fd(control->cmd->infile, cmd->outfile);
	close_pipes(control->pipe_fd, n_pipes);
	free_pipes(control->pipe_fd, n_pipes);
	dprintf(2, " 4: exit value: %d\n", status);
	execve(cmd->path_cmd, cmd->cmd_and_args, control->env);
	free_control(control);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	start_process(t_control *control, t_cmd *ptr_cmd, int i, int n_pipes)
{
	control->pid[i] = fork();
	if (control->pid[i] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (control->pid[i] == 0)
		children_exec(control, ptr_cmd, i, n_pipes);
}

void	multi_execution(t_control *control, int n_pipes)
{
	t_cmd	*ptr_cmd;
	int		i;

	control->pipe_fd = create_pipes(n_pipes);
	control->pid = (pid_t *)ft_calloc((n_pipes + 1), sizeof(pid_t));
	if (!control->pipe_fd)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ptr_cmd = control->cmd;
	i = 0;
	while (ptr_cmd && i < n_pipes + 1)
	{
		start_process(control, ptr_cmd, i, n_pipes);
		ptr_cmd = ptr_cmd->next;
		i++;
	}
	close_pipes(control->pipe_fd, n_pipes);
	control->status_cmd = handle_wait(control, n_pipes);
	update_env(control, ft_strdup("?"), ft_itoa(control->status_cmd), FALSE);
	free_pipes(control->pipe_fd, n_pipes);
	free(control->pid);
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
