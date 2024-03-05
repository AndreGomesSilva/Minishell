/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/04 22:58:53 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd_pipe(t_control *control)
{
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
	free_control(control);
}

static void	print_exit(t_control *control)
{
	if (!control->n_pipes)
		printf("exit\n");
}

static void	print_error_message(t_control *control, char **cmd, int i)
{
	char	*error_message;

	print_exit(control);
	error_message = swap_string(ft_strdup("exit: "), ft_strdup(cmd[i]));
	error_message = swap_string(error_message,
								ft_strdup(": numeric argument required\n"));
	ft_putstr_fd(error_message, 2);
	free(error_message);
	close_fd_pipe(control);
	exit(2);
}

long	is_valid_number(char *str)
{
	int	i;

	i = -1;
	if (!ft_atoi(str))
		return (FALSE);
	while (i++, str[i])
	{
		if (i == 0)
		{
			if (str[i] != '-' && str[i] != '+' && !ft_isdigit(str[i]))
				return (FALSE);
		}
		else
		{
			if (!ft_isdigit(str[i]))
				return (FALSE);
		}
	}
	return (TRUE);
}

void	handle_exit_builtin(t_control *control, char **cmd)
{
	int	second_param;

	if ((!cmd[1]))
	{
		print_exit(control);
		close_fd_pipe(control);
		exit(EXIT_SUCCESS);
	}
	else if (!is_valid_number(cmd[1]))
		print_error_message(control, cmd, 1);
	else if (ft_atoi((const char *)cmd[1]) && !cmd[2])
	{
		second_param = (int)ft_atoi((const char *)cmd[1]);
		print_exit(control);
		close_fd_pipe(control);
		if (second_param < 255)
			exit(second_param);
		exit(second_param % 256);
	}
	else if (ft_atoi((const char *)cmd[1]) && cmd[2])
	{
		print_exit(control);
		ft_putstr_fd("exit: too many arguments\n", 2);
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
	}
}
