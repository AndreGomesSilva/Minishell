/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:07:22 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/02 16:07:43 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_file(t_cmd *cmd, t_arg *ptr_arg)
{
	if (access(ptr_arg->next->arg, F_OK))
	{
		cmd->error_type = E_NO_FILE;
		ptr_arg->type = STOP;
		return (FALSE);
	}
	else if (access(ptr_arg->next->arg, R_OK))
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
