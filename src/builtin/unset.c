/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/26 16:08:08 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_unset_builtin(t_control *control, char **cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (i++, cmd[i])
	{
		str = ft_strjoin("$", cmd[i]);
		if (is_variable(str))
			remove_env(control, cmd[i]);
		else
		{
			printf("%s%s%s\n", "unset: `",cmd[i], "': not a valid identifier");
			update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
		}
		free(str);
	}
}
