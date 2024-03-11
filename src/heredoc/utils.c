/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:07:24 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/03 17:27:10 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify_broken_quote(t_control *control)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = control->cmd;
	if (ptr_cmd && ptr_cmd->type == BROKEN_QUOTES)
	{
		ptr_cmd->error_type = E_QUOTE;
		return (TRUE);
	}
	while (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		while (ptr_arg)
		{
			if (ptr_arg->type == BROKEN_QUOTES)
			{
				ptr_cmd->error_type = E_QUOTE;
				return (TRUE);
			}
			ptr_arg = ptr_arg->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
	return (FALSE);
}

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
			ptr_arg->type = IOFILE;
			eof = (ptr_arg->arg);
			break ;
		}
		ptr_arg = ptr_arg->next;
	}
	return (eof);
}

int	find_heredoc_arg(t_cmd *cmd)
{
	t_arg	*arg;
	int		result;

	arg = cmd->list_args;
	result = 0;
	while (arg)
	{
		if (arg->type == REDIRECT_HERD)
		{
			if (arg->next == NULL || arg->next->type > VAR_EXPAND)
				return (FALSE);
			else if (arg->next->type <= VAR_EXPAND)
			{
				arg->next->type = DOC;
				result = TRUE;
			}
		}
		arg = arg->next;
	}
	return (result);
}

int	find_heredoc_cmd(t_cmd *cmd)
{
	int	result;

	result = 0;
	if (cmd->type == REDIRECT_HERD)
	{
		if (cmd->list_args == NULL || cmd->list_args->type > VAR_EXPAND)
			return (FALSE);
		else if (cmd->list_args->type <= VAR_EXPAND)
		{
			cmd->list_args->type = DOC;
			result = TRUE;
		}
	}
	result += find_heredoc_arg(cmd);
	return (result);
}

int	create_heredoc_file(t_cmd *cmd, char *input, int *action)
{
	int		fd;
	char	*name;
	char	*file;

	name = ft_itoa(cmd->cmd_number);
	file = ft_strjoin("/tmp/", name);
	if (*action == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		cmd->error_type = E_NO_FILE;
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
	if (cmd->heredoc_file)
	{
		free(cmd->heredoc_file);
		cmd->heredoc_file = file;
	}
	else
		cmd->heredoc_file = file;
	free(name);
	return (TRUE);
}
