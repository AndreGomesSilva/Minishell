/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:44 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/03 18:51:32by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_files(t_cmd *cmd, char *file, int file_type, int *type)
{
	int	fd;
	
	fd = open(file, O_CREAT, 0666);
	if (fd == -1)
	{
		if (!*file)
			cmd->error_type = E_AMBIGUOUS;
		else
			cmd->error_type = E_NO_FILE;
	}
	else
		close(fd);
	if (access(file, W_OK))
	{
		cmd->error_type = E_PERMISSION;
		return (FALSE);
	}
	if (file_type == REDIRECT_OUTPUT)
		*type = 0;
	if (file_type == REDIRECT_OUTPUT_APPEND)
		*type = 1;
	return (TRUE);
}

char	*get_infile_arg(t_cmd *cmd, t_arg *ptr_arg)
{
	char	*file;

	file = NULL;
	if (ptr_arg)
	{
		if ((ptr_arg->type == REDIRECT_INPUT || ptr_arg->type == REDIRECT_HERD)
			&& ptr_arg->next && ptr_arg->next->type == IOFILE)
		{
			if (ptr_arg->type == REDIRECT_HERD)
				file = cmd->heredoc_file;
			else
			{
				if (ptr_arg->next)
				{
					if (!valid_file(cmd, ptr_arg->next))
						return (file);
					file = ptr_arg->next->arg;
				}
			}
		}
	}
	return (file);
}

char	*get_infile_cmd(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*file;

	file = NULL;
	ptr_arg = cmd->list_args;
	if ((cmd->type == REDIRECT_HERD || cmd->type == REDIRECT_INPUT) && ptr_arg)
	{
		if (cmd->type == REDIRECT_HERD)
			file = cmd->heredoc_file;
		else
		{
			if (!valid_file(cmd, ptr_arg))
				return (file);
			file = ptr_arg->arg;
		}
	}
	return (file);
}

char	*get_outfile_arg(t_cmd *cmd, int *type, t_arg *ptr_arg)
{
	char	*file;

	file = NULL;
	if (ptr_arg)
	{
		if (ptr_arg->type == STOP)
			return (file);
		else if (ptr_arg->type == REDIRECT_OUTPUT
			|| ptr_arg->type == REDIRECT_OUTPUT_APPEND)
		{
			if (ptr_arg->next && ptr_arg->next->type == IOFILE)
			{
				if (!create_files(cmd, ptr_arg->next->arg, ptr_arg->type, type))
					return (file);
				file = ptr_arg->next->arg;
			}
		}
	}
	return (file);
}

char	*get_outfile_cmd(t_cmd *cmd, int *type)
{
	t_arg	*ptr_arg;
	char	*file;

	file = NULL;
	ptr_arg = cmd->list_args;
	if (cmd->type == REDIRECT_OUTPUT || cmd->type == REDIRECT_OUTPUT_APPEND)
	{
		if (ptr_arg && ptr_arg->type == IOFILE)
		{
			if (!create_files(cmd, ptr_arg->arg, cmd->type, type))
				return (file);
			file = ptr_arg->arg;
		}
	}
	return (file);
}
