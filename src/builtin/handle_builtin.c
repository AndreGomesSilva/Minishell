/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:49:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/13 01:14:58 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtin(char **cmd, int fd, t_control *control)
{
	enum e_type_builtin	builtin;

	builtin = is_builtin(cmd[0]);
	if (builtin == B_CD || builtin == B_ECHO || builtin == B_EXPORT
		|| builtin == B_UNSET || builtin == B_ENV || builtin == B_EXIT
		|| builtin == B_PWD)
	{
		if (builtin == B_CD)
		{
			if (handle_cd(control, cmd[1]) == TRUE)
				return (TRUE);
		}
		else if (builtin == B_ECHO)
		{
			handle_echo(cmd, fd);
			return (TRUE);
		}
		else if (builtin == B_EXIT)
		{
			handle_exit(control);
			return (TRUE);
		}
		else if (builtin == B_ENV)
		{
			handle_env_builtin(control);
			return (TRUE);
		}
		else if (builtin == B_EXPORT)
		{
			handle_export(control, cmd);
			return (TRUE);
		}
		//	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		//		handle_unset(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		//		handle_pwd(cmd, fd);
	}
	else
		return (FALSE);
	return (TRUE);
}
