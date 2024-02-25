/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/24 21:00:47 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd_pipe(t_control *control)
{
	if(control->n_pipes > 0)
		close_pipes(control->pipe_fd, control->n_pipes);
	close_fd(control->cmd->infile, control->cmd->outfile);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_control(control);
}

void	handle_exit_builtin(t_control *control, char **cmd)
{
	int		return_exit;
	
	if ((!cmd[1]))
	{
		printf("exit\n");
		close_fd_pipe(control);
		exit(EXIT_SUCCESS);
	}
	if (ft_atoi((const char *)cmd[1]) && !cmd[2])
	{
		print_simple_error("EXIT_TWO");
		return_exit = (int)ft_atoi((const char *)cmd[1]) % 256;
		close_fd_pipe(control);
		exit(return_exit);
	}
	if (!ft_atoi((const char *)cmd[1]) && cmd[2])
	{
		printf("%s", "exit\n");
		update_env(control, "?", ft_strdup("2"));
		print_simple_error("EXIT_ERROR");
	}
	printf("%s", "exit\n");
	print_simple_error("EXIT");
}
