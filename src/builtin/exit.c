/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/24 17:29:52 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	handle_exit_builtin(t_control *control, char **cmd)
{
	if((!cmd[1]))
	{
		printf("exit\n");
		free_control(control);
		update_env(control, "?", ft_strdup("0"));
		exit(0);
	}
	if(ft_atoi((const char *)cmd[1]) && !cmd[2])
	{
		print_simple_error("EXIT_TWO");
		free_control(control);
		update_env(control, "?", ft_strdup(cmd[1]));
		exit(ft_atoi((const char *)cmd[1]) );
	}
	if(!ft_atoi((const char *)cmd[1]) && cmd[2])
	{
		printf("%s","exit\n");
		update_env(control, "?", ft_strdup("2"));
		print_simple_error("EXIT_ERROR");
	}
	printf("%s","exit\n");
	print_simple_error("EXIT");
}
