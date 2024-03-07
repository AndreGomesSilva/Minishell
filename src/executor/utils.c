/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:07:22 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/07 00:29:15 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	type_outfile_error(t_cmd *cmd, t_arg *ptr_arg, char *file)
{
	if (!*file && ptr_arg->prev_type == VAR_EXPAND)
		cmd->error_type = E_AMBIGUOUS;
	else if (opendir(file))
		cmd->error_type = E_IS_DIR;
	else
		cmd->error_type = E_NO_FILE;
	if ((!access(file, F_OK) && access(file, W_OK)) || (access(file, F_OK)
			&& *file && access(file, W_OK)))
		cmd->error_type = E_PERMISSION;
}

int	valid_file(t_cmd *cmd, t_arg *ptr_arg)
{
	if (access(ptr_arg->arg, F_OK))
	{
		if (ptr_arg && !*ptr_arg->arg)
			cmd->error_type = E_AMBIGUOUS;
		else
			cmd->error_type = E_NO_FILE;
		ptr_arg->type = STOP;
		return (FALSE);
	}
	else if (access(ptr_arg->arg, R_OK))
	{
		cmd->error_type = E_PERMISSION;
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
