/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:00 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/01 20:37:16 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	receive_signal_ctrl_d(t_control *control)
{
	int	status;

	status = 0;
	clear_history();
	printf("\n");
	status = ft_atoi(get_var_env(control, "?"));
	free_control(control);
	exit(status);
}

void	ctrl_c_heredoc(int sig)
{
	extern t_control	*g_control;

	(void)sig;
	update_env(g_control, ft_strdup("?"), ft_strdup("130"), FALSE);
	close(STDIN_FILENO);
	printf("\n");
}

void	ctrl_bar(int sig)
{
	extern t_control	*g_control;

	(void)sig;
	if (g_control->in_execution == 1)
	{
		update_env(g_control, ft_strdup("?"), ft_strdup("131"), FALSE);
		free_cmd(g_control);
		printf("Quit (core dumped)\n");
	}
}

void	receive_sig_int(int sig)
{
	extern t_control	*g_control;

	(void)sig;
	update_env(g_control, ft_strdup("?"), ft_strdup("130"), FALSE);
	free_cmd(g_control);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal(void)
{
	signal(SIGINT, receive_sig_int);
	signal(SIGQUIT, SIG_IGN);
}
