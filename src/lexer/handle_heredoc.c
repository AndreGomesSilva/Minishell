/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:11:45 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/10 14:08:02 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_next_eof(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*eof;

	eof = NULL;
	ptr_arg = cmd->list_args;
	while (ptr_arg)
	{
		if (ptr_arg->type == DOC)
		{
			ptr_arg->type = NORM;
			eof = (ptr_arg->arg);
			break ;
		}
		ptr_arg = ptr_arg->next;
	}
	return (eof);
}

void	create_heredoc_file(t_cmd *cmd, char *input, int file_action)
{
	int	fd;

	if (file_action == 1)
		fd = open(ft_itoa(cmd->cmd_number), O_WRONLY | O_CREAT | O_APPEND,
				0666);
	else
		fd = open(ft_itoa(cmd->cmd_number), O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		handle_error(cmd, NO_FILE);
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
	add_history(input);
}

int	heredoc_input(t_cmd *cmd, char *eof, int file_action)
{
	char	*input;
	int		flux_ctrl;

	flux_ctrl = 1;
	while (flux_ctrl)
	{
		input = readline("> ");
		if (input && *input)
		{
			flux_ctrl = ft_strncmp(eof, input, ft_strlen(input));
			if (flux_ctrl)
			{
				create_heredoc_file(cmd, input, file_action);
				file_action = 1;
			}
			free(input);
		}
	}
	return (file_action);
}

void	open_prompt(t_cmd *cmd)
{
	int		file_action;
	char	*eof;

	eof = get_next_eof(cmd);
	while (eof)
	{
		heredoc_input(cmd, eof, file_action);
		file_action = 0;
		eof = get_next_eof(cmd);
	}
}

void	handle_heredoc(t_control *control)
{
	t_cmd	*ptr_cmd;
	t_cmd	*next_cmd;

	ptr_cmd = control->cmd;
	while (ptr_cmd)
	{
		next_cmd = ptr_cmd->next;
		if (search_heredoc_cmd(ptr_cmd))
			open_prompt(ptr_cmd);
		ptr_cmd = next_cmd;
	}
}
