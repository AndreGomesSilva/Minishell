/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:40:48 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/29 21:51:42 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	multi_execution(t_control *control, int n_pipes)
{
	t_cmd	*ptr_cmd;
	int		i;

	control->pipe_fd = create_pipes(n_pipes);
	control->pid = (int *)ft_calloc(n_pipes + 2, sizeof(pid_t));
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
	control->in_execution = 0;
	update_env(control, ft_strdup("?"), ft_itoa(control->status_cmd), FALSE);
	free_pipes(control->pipe_fd, n_pipes);
	free(control->pid);
}

void	single_execution_builtin(t_control *control)
{
	t_cmd	*ptr_cmd;
	int		old_stdin;
	int		old_stdout;
	int		cmd_is_builtin;

	ptr_cmd = control->cmd;
	cmd_is_builtin = 0;
	handle_io(ptr_cmd, NULL, 0, FALSE);
	if (ptr_cmd->error_type)
		control->status_cmd = print_error(ptr_cmd);
	else if (ptr_cmd->infile == STDIN_FILENO
		&& ptr_cmd->outfile == STDOUT_FILENO)
		cmd_is_builtin = handle_builtin(ptr_cmd->cmd_and_args, control);
	else
	{
		old_stdin = dup(STDIN_FILENO);
		old_stdout = dup(STDOUT_FILENO);
		change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
		cmd_is_builtin = handle_builtin(ptr_cmd->cmd_and_args, control);
		change_stdio(old_stdin, old_stdout);
	}
	close_fd(control->cmd->infile, control->cmd->outfile);
	if (!cmd_is_builtin)
		update_env(control, ft_strdup("?"), ft_itoa(control->status_cmd),
			FALSE);
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
