/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:33:31 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/25 12:49:49 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_control	*g_control;

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	g_control = NULL;
	if (argc > 1)
		return (0);
	handle_config(&g_control, env);
	handle_signal();
	while (1)
		get_input(g_control);
	clear_history();
	free_control(g_control);
	return (0);
}
