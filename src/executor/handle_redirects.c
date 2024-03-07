/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:16:11 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/07 00:30:13 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_files(t_cmd *cmd, t_arg *ptr_arg, int file_type, int *type)
{
	int		fd;
	char	*file;

	file = ptr_arg->arg;
	if (file_type == REDIRECT_OUTPUT)
		*type = 0;
	else if (file_type == REDIRECT_OUTPUT_APPEND)
		*type = 1;
	if (*type == 0)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		type_outfile_error(cmd, ptr_arg, file);
		return (FALSE);
	}
	else
		close(fd);
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
	int		file_type;

	file = NULL;
	if (ptr_arg)
	{
		if (ptr_arg->type == STOP)
			return (file);
		else if ((ptr_arg->type == REDIRECT_OUTPUT
				|| ptr_arg->type == REDIRECT_OUTPUT_APPEND) && ptr_arg->next)
		{
			file_type = ptr_arg->type;
			ptr_arg = ptr_arg->next;
			if (ptr_arg->type == IOFILE)
			{
				if (!create_files(cmd, ptr_arg, file_type, type))
					return (file);
				file = ptr_arg->arg;
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
			if (!create_files(cmd, ptr_arg, cmd->type, type))
				return (file);
			file = ptr_arg->arg;
		}
	}
	return (file);
}
