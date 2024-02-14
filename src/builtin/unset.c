/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/14 02:30:05 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_unset(t_control *control, char **cmd)
{
	int	i;

	i = 0;
			
	while (i++, cmd[i])
			remove_env(control, cmd[i]);
}
