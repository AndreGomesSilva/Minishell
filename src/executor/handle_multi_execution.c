
#include "../../include/minishell.h"

static void finish_execution(t_control *control, t_cmd *cmd)
{
	close_fd(cmd->infile, cmd->outfile);
	close_pipes(control->pipe_fd, control->n_pipes);
	free_pipes(control->pipe_fd, control->n_pipes);
}

int	handle_wait(t_control *control)
{
	int		status;
	int		i;
	pid_t	pid;

	i = 0;
	while (i < control->n_pipes + 1 || pid > 0)
	{
		pid = waitpid(-1, &status, 2);
		if (WIFEXITED(status))
			status = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			status = (WTERMSIG(status));
		i++;
	}
	return (status);
}

static void	children_exec(t_control *control, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (cmd->cmd_and_args && handle_builtin(cmd->cmd_and_args, control))
	{
		finish_execution(control, cmd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		status = ft_atoi(get_var_env(control, "?"));
		free_control(control);
		exit(status);
	}
	finish_execution(control, cmd);
	execve(cmd->path_cmd, cmd->cmd_and_args, control->env);
	free_control(control);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	start_process(t_control *control, t_cmd *ptr_cmd, int i)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_io(ptr_cmd, control->pipe_fd, i, TRUE);
		if (ptr_cmd->error_type || !ptr_cmd->cmd_and_args)
		{
			finish_execution(control, ptr_cmd);
			if (ptr_cmd->type == REDIRECT_HERD)
				exit(0);
			control->status_cmd = print_error(ptr_cmd, ptr_cmd->error_type);
			status = control->status_cmd;
			free_control(control);
			exit(status);
		}
		change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
		children_exec(control, ptr_cmd);
	}
}

void	multi_execution(t_control *control, int n_pipes)
{
	t_cmd	*ptr_cmd;
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
		start_process(control, ptr_cmd, i);
		ptr_cmd = ptr_cmd->next;
		i++;
	}
	close_pipes(control->pipe_fd, n_pipes);
	control->status_cmd = handle_wait(control);
	update_env(control, ft_strdup("?"), ft_itoa(control->status_cmd), FALSE);
	free_pipes(control->pipe_fd, control->n_pipes);
}
