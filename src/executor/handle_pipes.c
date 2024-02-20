/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:58:13 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/19 21:06:02 by angomes-         ###   ########.fr       */
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

void	close_pipes(int **pipe_fd, int n_pipes)
{
	int		i;

	i = 0;
	while (i < n_pipes + 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}