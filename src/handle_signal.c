/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:00 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/11 23:59:26 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	receive_signal_ctrl_d(t_control *control)
{
	clear_history();
	free_control(control);
	exit(0);
}

void	receive_sig_int(int sig)
{
	extern t_control	*g_control;

	(void)sig;
	free_control(g_control);
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