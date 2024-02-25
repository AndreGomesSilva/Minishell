/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/25 19:56:35 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd_pipe(t_control *control)
{
	if (control->n_pipes > 0)
		close_pipes(control->pipe_fd, control->n_pipes);
	close_fd(control->cmd->infile, control->cmd->outfile);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_control(control);
}

void	handle_exit_builtin(t_control *control, char **cmd)
{
	if ((!cmd[1]))
	{
		printf("exit\n");
		close_fd_pipe(control);
		exit(EXIT_SUCCESS);
	}
	else if (ft_atoi((const char *)cmd[1]) && !cmd[2])
	{
		printf("%s", "exit\n");
		close_fd_pipe(control);
		exit((int)ft_atoi((const char *)cmd[1]) % 256);
	}
	else if (ft_atoi((const char *)cmd[1]) && !ft_atoi((const char *)cmd[1]))
	{
		printf("%s", "exit\n");
		printf("%s%s%s\n", "exit: ", cmd[1], ": too many arguments");
		update_env(control, ft_strdup("?"), ft_strdup("1"));
	}
	else if (!ft_atoi((const char *)cmd[1]) && cmd[2])
	{
		printf("%s", "exit\n");
		printf("%s%s%s\n", "exit: ", cmd[1], ": numeric argument required");
		exit(2);
	}
}
