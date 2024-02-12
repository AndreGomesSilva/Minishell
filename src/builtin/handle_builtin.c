/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:49:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 23:25:07 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtin(char **cmd, int fd, t_control *control)
{
	const enum e_type_builtin	builtin = is_builtin(cmd[0]);
	const enum e_type_builtin	builtin = is_builtin(cmd[0]);

	if (builtin == CD || builtin == ECHO || builtin == EXPORT
		|| builtin == UNSET || builtin == ENV || builtin == EXIT
		|| builtin == PWD)
	{
		if (builtin == CD)
		{
			if (handle_cd(control, cmd[1]) == TRUE)
				return (TRUE);
		}
		else if (builtin == ECHO)
		{
			handle_echo(cmd, fd);
			return (TRUE);
		}
		else if (builtin == EXIT)
		{
			handle_exit(control);
			return (TRUE);
		}
		else if (builtin == ENV)
		{
			handle_env_b(control);
			return (TRUE);
		}
		// else if (builtin == EXPORT)
		// {
		// 	handle_export(control, cmd);
		// 	return (TRUE);
		// }
		//	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		//		handle_unset(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		//		handle_cd(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		//		handle_pwd(cmd, fd);
	}
	else
		return (FALSE);
	return (TRUE);
}
