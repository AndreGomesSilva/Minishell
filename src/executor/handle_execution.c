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
#include <stdio.h>
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
	int		old_stdin;
	int		old_stdout;

	ptr_cmd = control->cmd;
	if (handle_io(ptr_cmd, NULL, 0, 0))
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
void free_pipes(int **pipes, int n_pipes)
{
	int i;
	i = 0;
	while (i < n_pipes + 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**create_pipes(int n_pipes)
{
	int		**pipes;
	int		i;

	pipes = (int **)ft_calloc((n_pipes + 1), sizeof(int*));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n_pipes + 1)
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

void multi_execution(t_control *control, int n_pipes) {
	t_cmd	*ptr_cmd;
	int		**pipe_fd;
	pid_t	pid;
	int		i;

	pipe_fd = create_pipes(n_pipes);
	if (!pipe_fd)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ptr_cmd = control->cmd;
    i = 0;

	while (ptr_cmd && i < n_pipes  + 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (handle_io(ptr_cmd, pipe_fd, i, 1))
			{
				change_stdio(ptr_cmd->infile, ptr_cmd->outfile);
				if (is_builtin(ptr_cmd->cmd))
				{
					handle_builtin(ptr_cmd->cmd_and_args, control);
					exit(EXIT_SUCCESS);
				}
				for (int j = 0; j < n_pipes + 1; j++) {
    	            close(pipe_fd[j][0]);
    		        close(pipe_fd[j][1]);
            	}
				execve(ptr_cmd->path_cmd, ptr_cmd->cmd_and_args, NULL);
   		    	perror("execve");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_FAILURE);
		}
		ptr_cmd = ptr_cmd->next;
		i++;
	}
    for (int i = 0; i < n_pipes + 1; i++) {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
    }

    for (int i = 0; i < n_pipes + 1; i++) {
        wait(NULL);
    }
	free_pipes(pipe_fd, n_pipes);
}

void	handle_execution(t_control *control)
{
	int		n_pipes;
	t_cmd	*ptr_cmd;

	ptr_cmd = control->cmd;
	n_pipes = 0;
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
