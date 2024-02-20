/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:41 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/20 20:00:06 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_env_builtin(t_control *control, char **cmd)
{
	if(!cmd[1])
		print_env(control->env_table);
	else
	 	print_simple_error("ENV");	
}
