/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:44 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/12 17:08:24 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_files(char *file)
{
	int	fd;

	fd = open(file, O_CREAT, 0666);
	if (fd == -1)
		return (FALSE);
	close(fd);
	return (TRUE);
}

int	handle_redirects(t_control *control)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;
	t_arg	*last_file;

	ptr_cmd = control->cmd;
	last_file = NULL;
	while (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		while (ptr_arg)
		{
			if (ptr_arg->type == IOFILE)
			{
				if (!create_files(ptr_arg->arg))
					print_error(ptr_cmd, NO_FILE);
				ptr_arg->type = NORM;
				last_file = ptr_arg;
			}
			ptr_arg = ptr_arg->next;
		}
		if (last_file)
			last_file->type = IOFILE;
		ptr_cmd = ptr_cmd->next;
	}
	return (TRUE);
}
