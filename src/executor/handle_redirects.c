/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:44 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/21 14:17:09 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_files(char *file, int type)
{
	int	fd;

	fd = -1;
	if (type == REDIRECT_OUTPUT)
		fd = open(file, O_CREAT, 0666);
	else if (type == REDIRECT_OUTPUT_APPEND)
		fd = open(file, O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (FALSE);
	close(fd);
	return (TRUE);
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
					print_error(cmd, E_NO_FILE);
				if (access(ptr_arg->next->arg, R_OK))
					print_error(cmd, E_PERMISSION);
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
		if (ptr_arg->type == REDIRECT_HERD)
			last_file = cmd->heredoc_file;
		else
		{
			if (access(ptr_arg->arg, F_OK))
				cmd->error_type = E_NO_FILE;
			if (access(ptr_arg->arg, R_OK))
				cmd->error_type = E_PERMISSION;
			last_file = ptr_arg->arg;
		}
	}
	temp = get_last_infile_arg(cmd);
	if (temp)
		last_file = temp;
	return (last_file);
}

char	*get_last_outfile_cmd(t_cmd *cmd)
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
				if (!create_files(ptr_arg->next->arg, ptr_arg->type))
					cmd->error_type = E_NO_FILE;
				last_file = ptr_arg->next->arg;
			}
		}
		ptr_arg = ptr_arg->next;
	}
	return (last_file);
}

char	*get_last_outfile(t_cmd *cmd)
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
			if (!create_files(ptr_arg->arg, cmd->type))
				cmd->error_type = E_NO_FILE;
			last_file = ptr_arg->arg;
		}
	}
	temp = get_last_outfile_cmd(cmd);
	if (temp)
		last_file = temp;
	return (last_file);
}
