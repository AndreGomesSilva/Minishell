/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:07:22 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/09 19:41:21 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	type_outfile_error(t_cmd *cmd, t_arg *ptr_arg, char *file)
{
	struct stat	path_stat;

	if (!*file && ptr_arg->prev_type == VAR_EXPAND)
		cmd->error_type = E_AMBIGUOUS;
	else if (stat(file, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		perror(file);
		cmd->error_type = E_IS_DIR;
	}
	else if (access(file, F_OK) || access(file, W_OK))
	{
		perror(file);
		cmd->error_type = E_NO_FILE;
	}
}

int	valid_file(t_cmd *cmd, t_arg *ptr_arg)
{
	if (access(ptr_arg->arg, F_OK) || access(ptr_arg->arg, R_OK))
	{
		if (ptr_arg && !*ptr_arg->arg)
			cmd->error_type = E_AMBIGUOUS;
		else
		{
			perror(ptr_arg->arg);
			cmd->error_type = E_NO_FILE;
		}
		ptr_arg->type = STOP;
		return (FALSE);
	}
	return (TRUE);
}

void	close_fd(int in, int out)
{
	if (in != STDIN_FILENO)
		close(in);
	if (out != STDOUT_FILENO)
		close(out);
}

void	change_stdio(int in, int out)
{
	if (in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
