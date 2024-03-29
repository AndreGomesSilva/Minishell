/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:24:03 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/09 18:24:12 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd_pipe(t_control *control, long *status_code)
{
	*status_code = ft_atoi((const char *)get_var_env(control, "?"));
	if (control->n_pipes > 0)
	{
		close(control->exit_fd[0]);
		close(control->exit_fd[1]);
		close_pipes(control->pipe_fd, control->n_pipes);
		free_pipes(control->pipe_fd, control->n_pipes);
		free(control->pid);
	}
	close_fd(control->cmd->infile, control->cmd->outfile);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	clear_history();
	free_control(control);
}

static void	print_exit(t_control *control)
{
	if (!control->n_pipes)
		printf("exit\n");
}

static void	print_error_message(t_control *control, char **cmd, int i,
		long *status_code)
{
	char	*error_message;

	print_exit(control);
	error_message = swap_string(ft_strdup("exit: "), ft_strdup(cmd[i]));
	error_message = swap_string(error_message,
			ft_strdup(": numeric argument required\n"));
	ft_putstr_fd(error_message, 2);
	free(error_message);
	close_fd_pipe(control, status_code);
	exit(2);
}

void	write_return_close_pipes(t_control *control, long *status_code,
		int type, char *cmd)
{
	if (type == 1)
	{
		update_env(control, ft_strdup("?"), ft_strdup(cmd), FALSE);
		close_fd_pipe(control, status_code);
	}
	else if (type == 2)
	{
		update_env(control, ft_strdup("?"), ft_strdup(cmd), FALSE);
		close_fd_pipe(control, status_code);
	}
}

void	handle_exit_builtin(t_control *control, char **cmd)
{
	long	status_code;

	if (!cmd[1])
	{
		status_code = ft_atoi((const char *)get_var_env(control, "?"));
		print_exit(control);
		write_return_close_pipes(control, &status_code, 1, "");
		exit(status_code);
	}
	if (!is_valid_number(cmd[1]))
		print_error_message(control, cmd, 1, &status_code);
	else if (is_valid_number(cmd[1]) && !cmd[2])
	{
		print_exit(control);
		write_return_close_pipes(control, &status_code, 2, cmd[1]);
		if (status_code < 255)
			exit(status_code);
		exit(status_code % 256);
	}
	else
	{
		print_exit(control);
		ft_putstr_fd("exit: too many arguments\n", 2);
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
	}
}
