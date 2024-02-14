/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:15 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/14 01:49:49 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_export(t_control *control, char **cmd)
{
	int	i;
	int	position_equal;

	i = 0;
	if (!cmd[1])
	{
		print_simple_error("EXPORT");
		return ;
	}
	while (i++, cmd[i])
	{
		position_equal = get_size_env_key(cmd[i]);
		if (position_equal != 0 && position_equal != -1)
		{
			update_env(control, ft_substr(cmd[i], 0, position_equal),
				ft_substr(cmd[i], position_equal + 1, ft_strlen(cmd[i])));
		}
		else
			print_simple_error("EXPORT");
	}
}
