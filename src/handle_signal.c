/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:00 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/20 23:40:38 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	receive_signal_ctrl_d(t_control *control)
{
	int exit_value;

	exit_value = control->exit_value;
	clear_history();
	printf("\n");
	free_control(control);
	exit(exit_value);
}

int	ctrl_d_herdoc(t_control *control, char *eof)
{
	(void)control;
	printf("heredoc: delimited by end-of-file (wanted `%s') \n", eof);
	return (0);
}

void	receive_sig_int(int sig)
{
	(void)sig;
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

// FIXME: Ctrl + C = apaga o que esta no buffer e desenha uma nova linha