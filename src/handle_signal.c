/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:00 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/19 17:40:58 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	receive_signal_ctrl_d(t_control *control)
{
	clear_history();
	printf("\n");
	free_control(control);
	exit(0);
}

int	ctrl_d_herdoc(t_control *control, char *eof)
{
	(void)control;
	printf("heredoc: delimited by end-of-file (wanted `%s') \n", eof);
	return (0);
}

void	receive_sig_int(int sig)
{
	extern t_control	*g_control;

	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal(void)
{
	extern t_control	*g_control;

	signal(SIGINT, receive_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

// FIXME: Ctrl + C = apaga o que esta no buffer e desenha uma nova linha