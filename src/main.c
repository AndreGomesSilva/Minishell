/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:33:31 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/08 16:33:32 by r-afonso         ###   ########.fr       */
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
		middleware(g_control);
	clear_history();
	free_control(g_control);
	return (0);
}
