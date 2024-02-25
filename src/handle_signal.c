/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:00 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/25 23:19:35 by r-afonso         ###   ########.fr       */
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

void	ctrl_c_heredoc(int sig)
{
	extern t_control	*g_control;

	(void)sig;
	update_env(g_control, ft_strdup("?"), ft_strdup("130"), FALSE);
	close (STDIN_FILENO);
	printf("\n");
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
