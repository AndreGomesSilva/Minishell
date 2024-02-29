/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:44 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/29 17:06:42 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_files(t_cmd *cmd, char *file, int file_type, int *type)
{
	int fd;

	if (!access(file, F_OK))
	{
		if (access(file, W_OK))
			cmd->error_type = E_PERMISSION;
	}
	else if (cmd->error_type == E_NO_ERROR)
	{
		fd = open(file, O_CREAT, 0666);
		close (fd);
	}
	if (file_type == REDIRECT_OUTPUT)
		*type = 0;
	if (file_type == REDIRECT_OUTPUT_APPEND)
		*type = 1;
}

char	*get_last_infile_arg(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*last_file;

	last_file = NULL;
	ptr_arg = cmd->list_args;
	while (ptr_arg)
	{
		if ((ptr_arg->type == REDIRECT_INPUT || ptr_arg->type == REDIRECT_HERD)
			&& ptr_arg->next && ptr_arg->next->type == IOFILE)
		{
			if (ptr_arg->type == REDIRECT_HERD)
				last_file = cmd->heredoc_file;
			else
			{
				if (access(ptr_arg->next->arg, F_OK))
					cmd->error_type = E_NO_FILE;
				else if (access(ptr_arg->next->arg, R_OK))
					cmd->error_type = E_PERMISSION;
				last_file = ptr_arg->next->arg;
			}
		}
		ptr_arg = ptr_arg->next;
	}
	return (last_file);
}

char	*get_last_infile(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*last_file;
	char	*temp;

	last_file = NULL;
	ptr_arg = cmd->list_args;
	if ((cmd->type == REDIRECT_HERD || cmd->type == REDIRECT_INPUT) && ptr_arg)
	{
		if (cmd->type == REDIRECT_HERD)
			last_file = cmd->heredoc_file;
		else
		{
			if (access(ptr_arg->arg, F_OK))
				cmd->error_type = E_NO_FILE;
			else if (access(ptr_arg->arg, R_OK))
				cmd->error_type = E_PERMISSION;
			last_file = ptr_arg->arg;
		}
	}
	temp = get_last_infile_arg(cmd);
	if (temp)
		last_file = temp;
	return (last_file);
}

char	*get_last_outfile_cmd(t_cmd *cmd, int *type)
{
	t_arg	*ptr_arg;
	char	*last_file;

	ptr_arg = cmd->list_args;
	last_file = NULL;
	while (ptr_arg)
	{
		if (ptr_arg->type == REDIRECT_OUTPUT
			|| ptr_arg->type == REDIRECT_OUTPUT_APPEND)
		{
			if (ptr_arg->next && ptr_arg->next->type == IOFILE)
			{
				create_files(cmd, ptr_arg->next->arg, ptr_arg->type, type);
				last_file = ptr_arg->next->arg;
			}
		}
		ptr_arg = ptr_arg->next;
	}
	return (last_file);
}

char	*get_last_outfile(t_cmd *cmd, int *type)
{
	t_arg	*ptr_arg;
	char	*last_file;
	char	*temp;

	last_file = NULL;
	ptr_arg = cmd->list_args;
	if (cmd->type == REDIRECT_OUTPUT || cmd->type == REDIRECT_OUTPUT_APPEND)
	{
		if (ptr_arg && ptr_arg->type == IOFILE)
		{
			create_files(cmd, ptr_arg->arg, cmd->type, type);
			last_file = ptr_arg->arg;
		}
	}
	temp = get_last_outfile_cmd(cmd, type);
	if (temp)
		last_file = temp;
	return (last_file);
}
