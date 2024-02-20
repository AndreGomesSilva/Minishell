/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:44 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/20 20:19:40 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

int	create_files(char *file)
{
	int	fd;

	fd = open(file, O_CREAT, 0666);
	if (fd == -1)
		return (FALSE);
	close(fd);
	return (TRUE);
}

char *get_last_infile(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*last_file;
	
	last_file = NULL;
	ptr_arg = cmd->list_args;
	if ((cmd->type == REDIRECT_HERD || cmd->type == REDIRECT_INPUT) && ptr_arg)
	{
		if (ptr_arg->type == REDIRECT_HERD)
				last_file = cmd->heredoc_file;
		else 
		{
			if (access(ptr_arg->arg, F_OK))
				print_error(cmd, E_NO_FILE);
			if (access(ptr_arg->arg, R_OK))
				print_error(cmd, E_PERMISSION);
			last_file = ptr_arg->arg;
		}
	}
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

char	*get_last_outfile(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*last_file;

	last_file = NULL;
	ptr_arg = cmd->list_args;
	while (ptr_arg)
	{
		if (ptr_arg->type == REDIRECT_OUTPUT || ptr_arg->type == REDIRECT_OUTPUT_APPEND)
		{
			if (ptr_arg->next && ptr_arg->next->type == IOFILE)
			{
				if (!create_files(ptr_arg->next->arg))
				{
					print_error(cmd, E_NO_FILE);
					return (NULL);
				}
				last_file = ptr_arg->next->arg;
			}
		}
		ptr_arg = ptr_arg->next;
	}
	return (last_file);
}
