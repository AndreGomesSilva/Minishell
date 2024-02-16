/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:44 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/16 14:48:14 by angomes-         ###   ########.fr       */
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

char	*get_last_outfile(t_cmd *cmd)
{
	t_arg	*ptr_arg;
	char	*last_file;

	last_file = NULL;
	ptr_arg = cmd->list_args;
	while (ptr_arg)
	{
		if (ptr_arg->type == REDIRECT_OUTPUT)
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
