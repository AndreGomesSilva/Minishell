/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/07 02:02:29 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_unset_builtin(t_control *control, char **cmd)
{
	int	i;

	i = 0;
	while (i++, cmd[i])
	{
		if(!ft_strncmp(cmd[i], "?",2) || !ft_strncmp(cmd[i], "_",2) ||  !ft_strncmp(cmd[i], "",1) || !ft_strncmp(cmd[i], "$",2))
			continue ;
		if (is_valid_env_name(cmd[i]))
				remove_env(control, cmd[i]);
		else
		{
			printf("%s%s%s\n", "unset: `", cmd[i], "': not a valid identifier");
			update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
		}
	}
}
