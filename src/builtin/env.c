/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:41 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 23:29:57 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_env_builtin(t_control *control)
{
	print_env(control->env_table);	
}
