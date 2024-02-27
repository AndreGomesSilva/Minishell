/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/26 21:21:31 by r-afonso         ###   ########.fr       */
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

static void	print_error_message(char **cmd, int i)
{
	char	*error_message;

	printf("%s", "exit\n");
	error_message = swap_string(ft_strdup("exit: `"), ft_strdup(cmd[i]));
	error_message = swap_string(error_message,
								ft_strdup("': numeric argument required\n"));
	ft_putstr_fd(error_message, 2);
	free(error_message);
	exit(2);
}

void	handle_exit_builtin(t_control *control, char **cmd)
{
	const int	retorno =(int)ft_atoi((const char *)cmd[1]);
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
		if (retorno < 255)
			exit(retorno);
		exit(retorno % 256);
	}
	else if (ft_atoi((const char *)cmd[1]) && cmd[2])
	{
		printf("%s", "exit\n");
		ft_putstr_fd("exit: too many arguments\n", 2);
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
	}
	else if (!ft_atoi((const char *)cmd[1]))
		print_error_message(cmd, 1);
}
