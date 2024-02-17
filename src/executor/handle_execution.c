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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
		handle_builtin(ptr_cmd->cmd_and_args, control);
		change_stdio(old_stdin, old_stdout);
		close_fd(ptr_cmd->infile, ptr_cmd->outfile);
		close_fd(old_stdin, old_stdout);
	}
}

void	multi_execution(t_control *control, int n_pipes)
{
	int 	pipe_fd[2];
	pid_t   pid;
	t_cmd	*ptr_cmd;
	int		i;
	
	ptr_cmd = control->cmd;
	i = 0;
	while (i < n_pipes + 1 && ptr_cmd)
	{
		
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (ptr_cmd->cmd_number == 1)
			{
				close(pipe_fd[0]);
				handle_io(ptr_cmd, pipe_fd);
				change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
				if (is_builtin(ptr_cmd->cmd))
				{
					handle_builtin(ptr_cmd->cmd_and_args, control);
					close_fd(ptr_cmd->infile, ptr_cmd->outfile);
					close(pipe_fd[1]);
					free_control(control);
					exit(EXIT_SUCCESS);
				}
				close_fd(ptr_cmd->infile, ptr_cmd->outfile);
				close(pipe_fd[1]);
				dprintf(2, "start -> r :%d\n", ptr_cmd->infile);
				dprintf(2, "start -> s :%d\n", ptr_cmd->outfile);
				execve(ptr_cmd->path_cmd,ptr_cmd->cmd_and_args, NULL);
				free_control(control);
				exit(EXIT_FAILURE);
			}
			if (!ptr_cmd->next)
			{
				close(pipe_fd[1]);
				handle_io(ptr_cmd, pipe_fd);
				change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
				if (is_builtin(ptr_cmd->cmd))
				{
					handle_builtin(ptr_cmd->cmd_and_args, control);
					close_fd(ptr_cmd->infile, ptr_cmd->outfile);
					close(pipe_fd[0]);
					free_control(control);
					exit(EXIT_SUCCESS);
				}
				close_fd(ptr_cmd->infile, ptr_cmd->outfile);
				close(pipe_fd[0]);
				dprintf(2, "end -> r :%d\n", ptr_cmd->infile);
				dprintf(2, "end -> s :%d\n", ptr_cmd->outfile);
				execve(ptr_cmd->path_cmd,ptr_cmd->cmd_and_args, NULL);
				free_control(control);
				exit(EXIT_FAILURE);
			}
			else 
			{
				handle_io(ptr_cmd, pipe_fd);
				change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
				if (is_builtin(ptr_cmd->cmd))
				{
					handle_builtin(ptr_cmd->cmd_and_args, control);
					close_fd(ptr_cmd->infile, ptr_cmd->outfile);
					close(pipe_fd[1]);
					close(pipe_fd[0]);
					free_control(control);
					exit(EXIT_SUCCESS);
				}
				close_fd(ptr_cmd->infile, ptr_cmd->outfile);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
				dprintf(2, " mid -> r :%d\n", ptr_cmd->infile);
				dprintf(2, " mid -> s :%d\n", ptr_cmd->outfile);
				execve(ptr_cmd->path_cmd,ptr_cmd->cmd_and_args, NULL);
				free_control(control);
				exit(EXIT_FAILURE);
			}
		}
		else 
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			ptr_cmd = ptr_cmd->next;
			i++;
		}
	}	
	// while (waitpid(-1, NULL, 0) > 0);
	int j;
	j = 0;
	while (j < n_pipes + 1)
	{
		waitpid(-1, NULL, 0);
		j++;
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
	else
		multi_execution(control, n_pipes);
}
