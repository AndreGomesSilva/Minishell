/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:41 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/25 23:17:13 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_env_builtin(t_control *control, char **cmd)
{
	if (!cmd[1])
		print_env(control->env_table);
	else
	{
		if(access(cmd[1], F_OK) == FALSE)
		{
			printf("%s%s%s\n", "env: `", cmd[1], "': Permission denied");
			update_env(control, ft_strdup("?"), ft_strdup("126"), FALSE);
		}
		else
		{
			printf("%s%s%s\n", "env: `", cmd[1], "': No such file or directory");
			update_env(control, ft_strdup("?"), ft_strdup("127"), FALSE);
		}
	}
}
